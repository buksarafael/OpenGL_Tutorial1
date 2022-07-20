#include <ShadersProgram.h>
bool readFile(const char* pFileName, std::string& outFile){
    std::ifstream f(pFileName);
    bool ret=false;
    if(f.is_open()){
        std::string line;
        while(getline(f,line)){
            outFile.append(line);
            outFile.append("\n");
        }
        f.close();
        ret=true;
    }
    else{
        std::cout<<"File error\n";
    }
    return ret;
}
void addShader(GLuint ShaderProgram,const char* pShaderText,GLenum ShaderType){
    GLuint ShaderObj = glCreateShader(ShaderType);
    if(ShaderObj==0){
        fprintf(stderr, "Error creating shader type %d\n",ShaderType);
        exit(0);
    }
    const GLchar* p[1];
    p[0]=pShaderText;
    GLint Lengths[1];
    Lengths[0]=(GLint)strlen(pShaderText);
    glShaderSource(ShaderObj,1,p,Lengths);
    glCompileShader(ShaderObj);

    GLint success;
    glGetShaderiv(ShaderObj,GL_COMPILE_STATUS,&success);
    if(!success){
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj,1024,NULL,InfoLog);
        fprintf(stderr,"Error compiling shader type %d: '%s'\n",ShaderType,InfoLog);
        exit(1);
    }
    glAttachShader(ShaderProgram,ShaderObj);
}

void ShadersProgram::initUniforms(){
    auto count=(std::size_t)Uniform::Count;
    for(std::size_t i =0;i<count;i++){
        const char* name=UniformHelper::getName((Uniform)i);
        int pos=glGetUniformLocation(m_ShaderProgram,name);
        if(pos==-1){
            m_Uniforms[i]=-1;
            continue;
        }
        m_Uniforms[i]=(GLuint)pos;
    }
}

GLint ShadersProgram::getUniformPosition(Uniform uniform){
    const char* name=UniformHelper::getName(uniform);
    return glGetUniformLocation(m_ShaderProgram,name);
}

void ShadersProgram::setUniform(Uniform uniform,int value){
    glUniform1i((std::size_t)uniform,value);
}
void ShadersProgram::setUniform(Uniform uniform,float value){
    glUniform1f((std::size_t)uniform,value);
}
void ShadersProgram::setUniform(Uniform uniform,Vector2f& vec2f){
    glUniform2f((std::size_t)uniform,vec2f.x,vec2f.y); 
}
void ShadersProgram::setUniform(Uniform uniform,Vector3f& vec3f){
    glUniform3f((std::size_t)uniform,vec3f.x,vec3f.y,vec3f.z);
}
void ShadersProgram::setUniform(Uniform uniform,Vector4f& vec4f){
    glUniform4f((std::size_t)uniform,vec4f.x,vec4f.y,vec4f.z,vec4f.w);
}
void ShadersProgram::setUniform(Uniform uniform,Matrix4f& mat4f){
    glUniformMatrix4fv(uniform,1,GL_TRUE,&mat4f.m[0][0]);
}

bool ShadersProgram::create(const std::array<const char *, 2> &files){
    this->m_ShaderProgram=glCreateProgram();
 
    if(m_ShaderProgram==0){
        fprintf(stderr,"Error creating shader program\n");
        exit(1);
    }

    std::string vs,fs;

    if(!readFile(files[0],vs)){
        std::cout<<"Can't read vertex shader file\n";
        exit(1);
    }
    addShader(m_ShaderProgram,vs.c_str(),GL_VERTEX_SHADER);

    if(!readFile(files[1],fs)){
        std::cout<<"Can't read fragment shader file\n";
        exit(1);
    }
    addShader(m_ShaderProgram,fs.c_str(),GL_FRAGMENT_SHADER);

    GLint Success=0;
    GLchar ErrorLog[1024]={0};

    glLinkProgram(m_ShaderProgram);
    glGetProgramiv(m_ShaderProgram,GL_LINK_STATUS,&Success);
    if(Success==0){
        glGetProgramInfoLog(m_ShaderProgram,sizeof(ErrorLog),NULL,ErrorLog);
        fprintf(stderr,"Error linking shader program: '%s'\n",ErrorLog);
        exit(1);
    }
    
    GLint gScaleLocation;
    gScaleLocation = glGetUniformLocation(m_ShaderProgram,"uOffset");
    if(gScaleLocation==-1){
        std::cout<<"Error getting uniform location of 'gScale'\n";
    }
    initUniforms();
    bindShaders();
}
void ShadersProgram::bindShaders(){
    glValidateProgram(this->m_ShaderProgram);
    glUseProgram(this->m_ShaderProgram);
}
