#include <ShadersProgram.h>
bool ShadersProgram::readFile(const char* pFileName, std::string& outFile){
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
void ShadersProgram::addShader(GLuint ShaderProgram,const char* pShaderText,GLenum ShaderType){
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

bool ShadersProgram::create(const std::array<const char *, 2> &files){
    GLuint ShaderProgram=glCreateProgram();

    if(ShaderProgram==0){
        fprintf(stderr,"Error creating shader program\n");
        exit(1);
    }

    std::string vs,fs;

    if(!readFile(files[0],vs)){
        std::cout<<"Can't read vertex shader file\n";
        exit(1);
    }
    addShader(ShaderProgram,vs.c_str(),GL_VERTEX_SHADER);

    if(!readFile(files[1],fs)){
        std::cout<<"Can't read fragment shader file\n";
        exit(1);
    }
    addShader(ShaderProgram,fs.c_str(),GL_FRAGMENT_SHADER);

    GLint Success=0;
    GLchar ErrorLog[1024]={0};

    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram,GL_LINK_STATUS,&Success);
    if(Success==0){
        glGetProgramInfoLog(ShaderProgram,sizeof(ErrorLog),NULL,ErrorLog);
        fprintf(stderr,"Error linking shader program: '%s'\n",ErrorLog);
        exit(1);
    }
    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram,GL_VALIDATE_STATUS,&Success);
    if(!Success){
        glGetProgramInfoLog(ShaderProgram,sizeof(ErrorLog),NULL,ErrorLog);
        fprintf(stderr,"Invalid shader program: '%s'\n");
        exit(1);
    }
    glUseProgram(ShaderProgram);

}