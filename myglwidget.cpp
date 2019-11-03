// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>
#include <iostream>
#include <fstream>
#include <sstream>


#include <OpenGL/gl3.h>
#include <GLUT/glut.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>


#include "myglwidget.h"

int read_stl(std::string fname, GLfloat * &vertices, GLfloat * &colors);

glm::mat4 MVP_grid, MVP_probe, Model_probe, Model_grid, Projection, View;

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);


MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
}

MyGLWidget::~MyGLWidget()
{
}

QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void MyGLWidget::setXRotation(int angle)
{
    //qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = 16*angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    //qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = 16*angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    //qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = 16*angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::initializeGL()
{

    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA | GLUT_DOUBLE);
    qglClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    draw();
}

void MyGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 20 * dy);
        setYRotation(yRot + 20 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 20 * dy);
        setZRotation(zRot + 20 * dx);
    }

    lastPos = event->pos();
}





GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

    // Create the shaders
    std::cout << "Version num " << glGetString(GL_VERSION)   << std::endl;
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }
    else
    {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;


    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 )
    {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }



    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 )
    {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }



    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 )
    {
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    
    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);
    
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}





void MyGLWidget::draw()
{
    GLuint programID = LoadShaders( "../TransformVertexShader.vertexshader", "../ColorFragmentShader.fragmentshader" );
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    Model_grid      = glm::mat4(1.0f);
	Model_grid      = glm::translate(Model_grid, glm::vec3(-5.0f, -5.0f, -5.0f));

	Model_probe      = glm::mat4(1.0f);
	Model_probe      = glm::translate(Model_probe, glm::vec3(6.5f, -1.5f, -1.8f));
	Model_probe      = glm::scale(Model_probe, glm::vec3(0.05f, 0.05f, 0.05f));
	Model_probe      = glm::eulerAngleXYZ( (float)(0.0f/180.0f * M_PI), (float)(0.0f/180.0f * M_PI),
					 (float)(90.0f/180.0f * M_PI)) * Model_probe;
	
	MVP_grid        = Projection * View * Model_grid;
	MVP_probe        = Projection * View * Model_probe;


    GLfloat *probevertices = NULL;
	GLfloat *probecolors = NULL;

    GLfloat *gridvertices = NULL;
	GLfloat *gridcolors = NULL;
    

    int probeindex = read_stl("../Submarine.stl", probevertices, probecolors);

    GLfloat *linevertices = new GLfloat[6];
	GLfloat linecolors[6] = {1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f};

	GLuint probevertexbuffer;
	glGenBuffers(1, &probevertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, probevertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, probeindex * sizeof(GLfloat), probevertices, GL_STATIC_DRAW);

	GLuint probecolorbuffer;
	glGenBuffers(1, &probecolorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, probecolorbuffer);
	glBufferData(GL_ARRAY_BUFFER, probeindex * sizeof(GLfloat), probecolors, GL_STATIC_DRAW);



    		/*
		############################################################################################################
											Rendering the probe
		############################################################################################################
		*/

    glBindBuffer(GL_ARRAY_BUFFER, probevertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, probecolorbuffer);
		
		glUseProgram(programID);
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP_probe[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, probevertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, probecolorbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		glDrawArrays(GL_TRIANGLES, 0, probeindex); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
}
    

int read_stl(std::string file_name, GLfloat * &vertices, GLfloat * &colors)
{

    std::ifstream myfile (file_name.c_str(), std::ios::in | std::ios::binary);

    char header_info[80] = "";
    char bin_n_triangles[4];
    unsigned int num_traingles;

    if (myfile) 
    {
        myfile.read (header_info, 80);
        std::cout <<"Header : " << header_info << std::endl;
    }

    if (myfile) 
    {
        myfile.read (bin_n_triangles, 4);
        num_traingles = *((unsigned int*)bin_n_triangles) ;
        std::cout <<"Number of triangles : " << num_traingles << std::endl;
    }

    vertices = new GLfloat[num_traingles * 9];
    colors = new GLfloat[num_traingles * 9];

    int index = 0;
    for(int i = 0; i < num_traingles; i++)
    {
        char facet[50];
        if (myfile) 
        {
            myfile.read (facet, 50);

            vertices[index++] = *( (float*) ( ( (char*)facet)+12));
            vertices[index++] = *( (float*) ( ( (char*)facet)+16));
            vertices[index++] = *( (float*) ( ( (char*)facet)+20));
            
            vertices[index++] = *( (float*) ( ( (char*)facet)+24));
            vertices[index++] = *( (float*) ( ( (char*)facet)+28));
            vertices[index++] = *( (float*) ( ( (char*)facet)+32));

            vertices[index++] = *( (float*) ( ( (char*)facet)+36));
            vertices[index++] = *( (float*) ( ( (char*)facet)+40));
            vertices[index++] = *( (float*) ( ( (char*)facet)+44));

            for(int x = index-9; x < index; ++x)
                colors[x] = 1.0f;
        }
    }

    return index;

}

