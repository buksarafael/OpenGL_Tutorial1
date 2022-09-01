#include <ShadersProgram.h>
#include <AttributeHelper.h>

bool BlendingState::equals(const BlendingState &cmp) const {
    return enabled == cmp.enabled && source_func == cmp.source_func && dest_func == cmp.dest_func;
}

bool BlendingState::operator==(const BlendingState &other) const {
    return this->equals(other);
}

bool BlendingState::operator!=(const BlendingState &other) const {
    return !this->equals(other);
}

bool BlendingState::operator<(const BlendingState &other) const {
    if(enabled != other.enabled)
        return enabled < other.enabled;
    if(source_func != other.source_func)
        return source_func <other.source_func;
    return dest_func < other.dest_func;
}

ShadersProgram::ShadersProgram(){};
ShadersProgram::~ShadersProgram(){};

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
    auto count=(std::size_t)UniformHelper::UniformType::kUniformCount;
    for(std::size_t i =0;i<count;i++){
        const char* name=UniformHelper::getUniformName((UniformHelper::UniformType)i);
        int pos=glGetUniformLocation(m_ShaderProgram,name);
        if(pos==-1){
            m_Uniforms[i]=-1;
            continue;
        }
        m_Uniforms[i]=(GLuint)pos;
    }
}

GLint ShadersProgram::getUniformPosition(UniformHelper::UniformType uniform){
    const char* name=UniformHelper::getUniformName(uniform);
    auto xd = glGetUniformLocation(m_ShaderProgram,name);
    return xd;
}

void ShadersProgram::setUniform(UniformHelper::UniformType uniform,int value){
    glUniform1i(getUniformPosition(uniform),value);
}
void ShadersProgram::setUniform(UniformHelper::UniformType uniform,float value){
    glUniform1f(getUniformPosition(uniform),value);
}
void ShadersProgram::setUniform(UniformHelper::UniformType uniform,Vector2f& vec2f){
    glUniform2f(getUniformPosition(uniform),vec2f.x,vec2f.y); 
}
void ShadersProgram::setUniform(UniformHelper::UniformType uniform,Vector3f& vec3f){
    glUniform3f(getUniformPosition(uniform),vec3f.x,vec3f.y,vec3f.z);
}
void ShadersProgram::setUniform(UniformHelper::UniformType uniform,Vector4f& vec4f){
    glUniform4f(getUniformPosition(uniform),vec4f.x,vec4f.y,vec4f.z,vec4f.w);
}
void ShadersProgram::setUniform(UniformHelper::UniformType uniform,Matrix4f& mat4f){
    glUniformMatrix4fv(getUniformPosition(uniform),1,GL_TRUE,&mat4f.m[0][0]);
}
bool ShadersProgram::create(const char *vs,const char *fs){
    std::array<const char*,2> files={vs,fs};
    create(files);
    return true;
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

    for(std::size_t i = 0; i < AttributeHelper::kAttributeCount;i++)
    {
        glBindAttribLocation(m_ShaderProgram, i, AttributeHelper::getAttributeName((AttributeHelper::AttributeType)i));
    }

    glLinkProgram(m_ShaderProgram);
    glGetProgramiv(m_ShaderProgram,GL_LINK_STATUS,&Success);
    if(Success==0){
        glGetProgramInfoLog(m_ShaderProgram,sizeof(ErrorLog),NULL,ErrorLog);
        fprintf(stderr,"Error linking shader program: '%s'\n",ErrorLog);
        exit(1);
    }
    
    initUniforms();
    
    //return true;
}
void ShadersProgram::bindShaders(){
    glUseProgram(this->m_ShaderProgram);
}
