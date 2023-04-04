#include <stdio.h>           // Standard C/C++ Input-Output
#include <math.h>            // Math Functions
#include <windows.h>         // Standard Header For MSWindows Applications
#include <gl/glut.h>            // The GL Utility Toolkit (GLUT) Header
#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// The Following Directive Fixes The Problem With Extra Console Window
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

// Uncomment the following if you want to use the glut library from the current directory
//#pragma comment(lib, "lib/glut32.lib")

// Global Variables
bool g_gamemode;				// GLUT GameMode ON/OFF
bool g_fullscreen;				// Fullscreen Mode ON/OFF (When g_gamemode Is OFF)
bool b_culling = false;			// Culling Enabled is Mandatory for this assignment do not change
float aspect = 1;

const float PI = 3.1415926535897932384626433832795028;
const float epsilon = 0.001;

//Function Prototypes
void render(void);
void initLights(void);
bool init(void);
void reshape(int w, int h);
//void keyboard(unsigned char key, int x, int y);
void special_keys(int a_keys, int x, int y);
//void drawAxes();
//void movingLight();

float angle = 0;
float temp = 0;
float temp2 = 0;
int temp3 = 0;
bool movingLightFlag = false;


void cylinder(float height, float radius, float red, float green, float blue) {
	float x = 0.0;
	float y = 0.0;
	float angle = 0.0;
	float angle_stepsize = 0.1;

	//Drawing the tube
	glColor3ub(red, green, blue); //adding color
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();

	//Circle on top of cylinder //
	glColor3ub(red, green, blue); //adding color
	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glEnd();

}


void cylinderB(float height, float radius, float red, float green, float blue) {
	float x = 0;
	float y = -100.0;
	float angle = 0.0;
	float angle_stepsize = 0.1;

	//Drawing the tube
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	int counter = 0;
	while (angle < 2 * PI) {
		//glColor3f(1.0f, 1.0f, 1.0f);
		x = radius * cos(angle);
		y = radius * sin(angle);


		if (counter % 2 == 0) {              // create the stripes
			glColor3f(0.0f, 0.0f, 1.0f);//Blue
			glVertex3f(x, y, height);
			glVertex3f(x, y, 0.0);
		}
		else {
			glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
			glVertex3f(x, y, height);
			glVertex3f(x, y, 0.0);

		}

		//glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
		counter++;
	}

	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();

	//Drawing the tube
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	counter = 0;
	while (angle < 2 * PI) {
		//glColor3f(1.0f, 1.0f, 1.0f);
		x = radius * cos(angle);
		y = radius * sin(angle);


		if (counter % 2 != 0) {        // create the stripes
			glColor3f(0.0f, 0.5f, 1.0f);//baby Blue
			glVertex3f(-x, -y, height);
			glVertex3f(-x, -y, 0.0);
		}
		else {
			glColor4f(1.0f, 1.0f, 0.0f, 0.0f);//yellow
			glVertex3f(-x, -y, height);
			glVertex3f(-x, -y, 0.0);

		}

		//glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
		counter++;
	}

	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();



	//Circle on top of cylinder //
	glColor3f(0.0f, 0.5f, 1.0f);//baby Blue color
	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glEnd();

}


void cylinderforPony(float height, float radius, float red, float blue, float green) {
	float x = 0.0;
	float y = -100.0;
	float angle = 0.0;
	float angle_stepsize = 0.01;

	/** Draw the tube */
	glColor3f(red, blue, green);//adding color
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();

	//Circle on top of cylinder //
	glColor3f(red, blue, green);//adding color 
	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glEnd();

}

void Sphere(double r, int lats, int longs) {
	int i, j;
	for (i = 0; i <= lats; i++) {
		double lat0 = PI * (-0.5 + (double)(i - 1) / lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = PI * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= longs; j++) {
			double lng = 2 * PI * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(r * x * zr0, r * y * zr0, r * z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(r * x * zr1, r * y * zr1, r * z1);
		}
		glEnd();
	}
}



void initLights(void) {

	//light 1
	GLfloat light_ambient[] = { 0.2,0.2,0.2,1 };
	GLfloat light_diffuse[] = { 0.8,0.8,0.8,1 };
	GLfloat light_position[] = { 0.0, 0.0, +5.0,1.0 };
	GLfloat spot_direction[] = { -1.0, 0.0, +1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	
	//light3
	GLfloat light3_position[] = { 0.0, 10.0,5.0, 1.0 };

	glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
	
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHTING);// Enable Lighting
}


// Our GL Specific Initializations. Returns true On Success, false On Fail.
bool init(void)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);             // Pixel Storage Mode To Byte Alignment
	glEnable(GL_TEXTURE_2D);                           // Enable Texture Mapping 
	glClearColor(1.0f, 1.0f, 1.0f, 1.0);			   // Light Blue Background 
	glClearDepth(1.0f);								   // Depth Buffer Setup
	glDepthFunc(GL_LEQUAL);							   // The Type Of Depth Testing To Do
	glEnable(GL_DEPTH_TEST);						   // Enables Depth Testing
	glShadeModel(GL_SMOOTH);						   // Enable Smooth Shading
	initLights();
	glEnable(GL_COLOR_MATERIAL);					   // Enable Material Coloring
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Hint for nice perspective interpolation
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);	// Set the color tracking for both faces for both the ambient and diffuse components

	//// Set Specular
	//GLfloat matSpec[] = { 0.1, 0.1,0.1,1 };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	//GLfloat shininess[] = { 64 };
	//glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_NORMALIZE);
	glFrontFace(GL_CCW);                               //Counter Clock Wise definition of the front and back side of faces
	glCullFace(GL_BACK);                               //Hide the back side

	return true;
}

void positionCamera() {

	glMatrixMode(GL_PROJECTION);     // Select The Projection Matrix

	glLoadIdentity();                // Reset The Projection Matrix
	gluPerspective(45.0f, aspect, 0.2, 100.0);
	gluLookAt(0.0f, 0.0f, 30.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//gluLookAt(10.0f,- 10.0f, 60.0f, 10.0f, -10.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	//camera transformations go here
	glMatrixMode(GL_MODELVIEW);      // Select The Modelview Matrix

}

// Our Reshaping Handler (Required Even In Fullscreen-Only Modes)
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	// Calculate The Aspect Ratio And Set The Clipping Volume
	if (h == 0) h = 1;
	aspect = (float)w / (float)h;
	positionCamera();
	glMatrixMode(GL_MODELVIEW);      // Select The Modelview Matrix
	glLoadIdentity(); // Reset The Modelview Matrix
	initLights();
}

// Our Keyboard Handler (Normal Keys)


// Our Keyboard Handler For Special Keys (Like Arrow Keys And Function Keys)
void special_keys(int a_keys, int x, int y)
{

	switch (a_keys) {
	case GLUT_KEY_F1:
		// We Can Switch Between Windowed Mode And Fullscreen Mode Only
		if (!g_gamemode) {
			g_fullscreen = !g_fullscreen;       // Toggle g_fullscreen Flag
			if (g_fullscreen) glutFullScreen(); // We Went In Fullscreen Mode
			else glutReshapeWindow(500, 500);   // We Went In Windowed Mode
		}
		break;
	case GLUT_KEY_UP:

		break;
	case GLUT_KEY_DOWN:

		break;
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	default:
		;
	}

	glutPostRedisplay();
}

void mouseButton(int button, int state, int x, int y) {
	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_UP) // state = GLUT_DOWN
		{
			temp2 = 0;
			//Do something
		}
		else // state = GLUT_DOWN
		{
			temp2 = 45;
			// Do something Else
		}
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN) // state = GLUT_DOWN
		{
			temp2 -= 1;
			//Do something
		}

	}
}

void mouseMove(int x, int y) {
	// Do what ever you want here, x & y is the position of the mouse
	printf("Mouse position is: %i in X axis and %i in Y axis\n", x, y);
}



// Main Function For Bringing It All Together.
int main(int argc, char** argv)
{
	glutInit(&argc, argv);                           // GLUT Initializtion
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE); // (CHANGED)|
	if (g_gamemode) {
		glutGameModeString("1024x768:32");            // Select 1024x768 In 32bpp Mode
		if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
			glutEnterGameMode();                     // Enter Full Screen
		else
			g_gamemode = false;                     // Cannot Enter Game Mode, Switch To Windowed
	}
	if (!g_gamemode) {
		glutInitWindowPosition(120, 100); // Window Position
		glutInitWindowSize(600, 700); // Window Size If We Start In Windowed Mode
		glutCreateWindow("EPL426 Homework"); // Window Title
		//int screenSize[] = { glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT) };
		//int windowsSize[] = { 1000,1000 };
		//glutInitWindowPosition((screenSize[0]/2) - (windowsSize[0]/2), (screenSize[1] / 2) - (windowsSize[1] / 2));
		//glutInitWindowSize(windowsSize[0], windowsSize[1]);
		//glutCreateWindow("EPL426 - 1st Assignment");
	}
	if (!init()) {                                   // Our Initialization
		fprintf(stderr, "Initialization failed.");
		return -1;
	}
	glutDisplayFunc(render);                     // Register The Display Function
	glutReshapeFunc(reshape);                    // Register The Reshape Handler
	//glutKeyboardFunc(keyboard);                  // Register The Keyboard Handler
	glutSpecialFunc(special_keys);               // Register Special Keys Handler
	glutMouseFunc(mouseButton);					 // Register Mouse buttons
	glutMotionFunc(mouseMove);					 // Register Mouse motion
	glutIdleFunc(NULL);                        	 // We Do Rendering In Idle Time
	glutMainLoop();                              // Go To GLUT Main Loop
	return 0;
}

void creating_cats(int i, float red, float blue, float green) {
	float r = 6.0;

	//left ear !!!!!!!!!!
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-1.5, 0.0, 2.7);
	glRotatef(-40, -110.0, -110.0, 0.0); // change the angle of the cyclinder , the x-postion , the y-position 
	glutSolidCone(0.5, 0.9, 30.0, 30.0); //create a solid cone
	glPopMatrix();

	//right ear !!!!!!!!!!
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-1.5, 0.0, 2.7);
	glRotatef(-40, +110.0, +110.0, 0.0); // change the angle of the cyclinder , the x-postion , the y-position 
	glutSolidCone(0.5, 0.9, 30.0, 30.0); //create a solid cone
	glPopMatrix();


	//mustach of the cat
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-2.2, 0.0, 2.7);
	glRotatef(65, 1.2, 0, 0.0);
	cylinderforPony(0.6, 0.05, red, blue, green);

	glPopMatrix();

	//mustach of the cat
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-2.2, 0.0, 2.7);
	glRotatef(-60, 1.0, 0, 0.0);
	cylinderforPony(0.6, 0.05, red, blue, green);

	glPopMatrix();


	//mustach of the cat
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-2.2, 0.0, 2.7);
	glRotatef(85, 1.2, 0, 0.0);
	cylinderforPony(0.6, 0.05, red, blue, green);

	glPopMatrix();


	//mustach of the cat
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-2.2, 0.0, 2.7);
	glRotatef(-80, 1.0, 0, 0.0);
	cylinderforPony(0.6, 0.05, red, blue, green);

	glPopMatrix();


	//mustach of the cat
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-2.2, 0.0, 2.7);
	glRotatef(105, 1.2, 0, 0.0);
	cylinderforPony(0.6, 0.05, red, blue, green);

	glPopMatrix();

	//mustach of the cat
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-2.2, 0.0, 2.7);
	glRotatef(-100, 1.2, 0, 0.0);
	cylinderforPony(0.6, 0.05, red, blue, green);

	glPopMatrix();


	//front face 

	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-1.5, 0.0, 2.7);
	glRotatef(-90, -6.0, 70.0, 0.0); // change the angle of the cyclinder , the x-postion , the y-position 
	glutSolidCone(0.5, 1.0, 30.0, 30.0);  //create a solid cone
	glPopMatrix();


	//head 
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-1.5, 0.0, 2.7);
	glRotatef(-40, -6.0, 70.0, 0.0); // change the angle of the cyclinder , the x-postion , the y-position 
	Sphere(0.5, 30, 30); //creating a sphere 
	glPopMatrix();

	//neck
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-0.5, 0.0, 2.0);
	glRotatef(-60, -5.0, 70.0, 0.0); // change the angle of the cyclinder and the x-postion
	cylinderforPony(1.0, 0.3, red, blue, green); //creating the body of the pony
	glPopMatrix();


	//body
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-1.0, 0.0, 2.0);
	glRotatef(90, -5.0, 70.0, 0.0); // change the angle of the cyclinder and the x-postion
	cylinderforPony(1.8, 0.4, red, blue, green); //creating the body of the pony
	glPopMatrix();

	//front body
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-0.9, 0.0, 2.0);
	glRotatef(90, -5.0, 70.0, 0.0); // change the angle of the cyclinder and the x-postion
	Sphere(0.4, 30, 30); //creating the front body of the pony
	glPopMatrix();

	//back body 
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(+0.8, 0.0, 2.0);
	glRotatef(90, -5.0, 70.0, 0.0); // change the angle of the cyclinder and the x-postion
	Sphere(0.4, 30, 30); //creating the front body of the pony
	glPopMatrix();

	//tail
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(+1.6, 0.0, +1.0);
	glRotatef(-30, -4.0, 60.0, 0.0);
	cylinderforPony(1.5, 0.1, red, blue, green);
	glPopMatrix();


	//hair of tales
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(+1.6, 0.0, +1.0);
	glRotatef(-90, -5.0, 60.0, 0.0);
	Sphere(0.2, 10, 10);
	glPopMatrix();


	//front-right leg  
	glPushMatrix();
	//glColor3f(red, blue, green);//adding color
	glTranslatef(-0.5, 0.2, 0.8);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	cylinderforPony(1.5, 0.1, red, blue, green);
	glPopMatrix();


	//front-left leg
	glPushMatrix();
	//glColor3f(red, blue, green);//adding color
	glTranslatef(-0.5, -0.2, 0.8);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	cylinderforPony(1.5, 0.1, red, blue, green);
	glPopMatrix();




	//behind-right leg
	glPushMatrix();
	//glColor3f(red, blue, green);//adding color
	glTranslatef(+0.5, 0.2, 0.8);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	cylinderforPony(1.5, 0.1, red, blue, green);
	glPopMatrix();



	//behind left leg 
	glPushMatrix();
	//glColor3f(red, blue, green);//adding color
	glTranslatef(+0.5, -0.2, 0.8);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	cylinderforPony(1.5, 0.1, red, blue, green);
	glPopMatrix();


}

void creating_pony(int i, float red, float blue, float green) {
	float r = 6.0;

	//left ear !!!!!!!!!!
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-1.0, 0.2, 2.7);
	glRotatef(0.0, -120.0, -110.0, 0.0); // change the angle of the cyclinder , the x-postion , the y-position 
	//cylinderforHorses(1.0, 0.1, 240, 248, 255); //creating the body of the pony
	//glutSolidCone(0.5, 0.9, 30.0, 30.0); //create a solid cone
	cylinderforPony(0.5, 0.1, red, blue, green);
	glPopMatrix();

	//right ear !!!!!!!!!!
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-1.0, -0.2, 2.7);
	glRotatef(0.0, +120.0, +110.0, 0.0); // change the angle of the cyclinder , the x-postion , the y-position 
	//glutSolidCone(0.5, 0.9, 30.0, 30.0); //create a solid cone
	cylinderforPony(0.5, 0.1, red, blue, green);
	glPopMatrix();


	//front-nose part
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-2.5, 0.0, 2.5);
	glRotatef(-90, -6.0, 70.0, 0.0); // change the angle of the cyclinder , the x-postion , the y-position 
	Sphere(0.2, 10, 10);
	glPopMatrix(); //creating the front nose part


	//back-nose part
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-2.0, 0.0, 2.5);
	glRotatef(-90, -6.0, 70.0, 0.0); // change the angle of the cyclinder , the x-postion , the y-position 
	cylinderforPony(0.5, 0.2, red, blue, green); // creating the back-nose part
	glPopMatrix();



	//front face 
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-1.9, 0.0, 2.5);
	glRotatef(-90, -6.0, 70.0, 0.0); // change the angle of the cyclinder , the x-postion , the y-position 
	Sphere(0.3, 30, 30);  //create a sphere
	glPopMatrix();


	//head 
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-0.9, 0.0, 2.5);
	glRotatef(-90, -5.0, 70.0, 0.0); // change the angle of the cyclinder and the x-postion 
	//Sphere(0.5, 30, 30); //creating a sphere 
	cylinderforPony(1.0, 0.3, red, blue, green); //creating the head
	glPopMatrix();

	//behind head
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-0.8, 0.0, 2.5);
	glRotatef(-90, -5.0, 70.0, 0.0); // change the angle of the cyclinder and the x-postion 
	Sphere(0.3, 30, 30);
	glPopMatrix();

	//body
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-1.0, 0.0, 2.0);
	glRotatef(90, -5.0, 70.0, 0.0); // change the angle of the cyclinder and the x-postion
	cylinderforPony(1.8, 0.4, red, blue, green); //creating the body of the pony
	glPopMatrix();

	//front body
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(-0.9, 0.0, 2.0);
	glRotatef(90, -5.0, 70.0, 0.0); // change the angle of the cyclinder and the x-postion
	Sphere(0.4, 30, 30); //creating the front body of the pony
	glPopMatrix();

	//back body 
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(+0.8, 0.0, 2.0);
	glRotatef(90, -5.0, 70.0, 0.0); // change the angle of the cyclinder and the x-postion
	Sphere(0.4, 30, 30); //creating the front body of the pony
	glPopMatrix();


	//tail
	glPushMatrix();
	//glColor3f(red, blue, green);//adding color
	glTranslatef(+1.5, 0.0, +1.0);
	glRotatef(-30, -4.0, 60.0, 0.0);
	cylinderforPony(1.5, 0.1, red, blue, green);
	glPopMatrix();


	//hair of tales
	glPushMatrix();
	glColor3f(red, blue, green);//adding color
	glTranslatef(+1.6, 0.0, +1.0);
	glRotatef(-90, -5.0, 60.0, 0.0);
	Sphere(0.2, 10, 10);
	glPopMatrix();


	//front-right leg  
	glPushMatrix();
	//glColor3f(red, blue, green);//adding color
	glTranslatef(-1.0, 0.2, 0.8);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	cylinderforPony(1.5, 0.1, red, blue, green);
	glPopMatrix();


	//front-left leg
	glPushMatrix();
	//glColor3f(red, blue, green);//adding color
	glTranslatef(-1.0, -0.2, 0.8);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	cylinderforPony(1.5, 0.1, red, blue, green);
	glPopMatrix();


	//behind-right leg
	glPushMatrix();
	//glColor3f(red, blue, green);//adding color
	glTranslatef(+0.8, 0.2, 0.8);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	cylinderforPony(1.5, 0.1, red, blue, green);
	glPopMatrix();



	//behind left leg 
	glPushMatrix();
	//glColor3f(red, blue, green);//adding color
	glTranslatef(+0.8, -0.2, 0.8);
	glRotatef(0.0, 0.0, 0.0, 0.0);
	cylinderforPony(1.5, 0.1, red, blue, green);
	glPopMatrix();


}

//the moon with texture
void draw_moon() {

	glColor3f(1.0f, 1.0f, 1.0f); //color of the moon

	Sphere(1.0, 100, 100); //craeting sphere for the moon
	//glPopAttrib();
}

void draw_sun() {
	glPushAttrib(GL_CURRENT_BIT);
	//enable blending 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// sphere 1
	glColor4f(1.0f, 1.f, .2f, 1.0f); //yellow color 
	Sphere(.6, 20, 20); // creating sphere for the sun

	// sphere 2
	glColor4f(1.0f, 1.f, .3f, 0.5);//yellow color 
	glutSolidSphere(1., 20, 20);// creating sphere for the sun

	// sphere 3
	glColor4f(1.0f, 1.f, .4f, 0.2f);//yellow color 
	glutSolidSphere(1.4, 20, 20);// creating sphere for the sun

	// sphere 4
	glColor4f(1.0f, 1.f, .5f, 0.2f);//yellow color 
	glutSolidSphere(1.8, 20, 20);// creating sphere for the sun

	glDisable(GL_BLEND);
	glPopAttrib();
}

float day_to_night = 0;
bool gray = FALSE;

//Colors for the animals
//Lilac , blue , blue-green , orange , purple , brown 
float red_color[] = { 2.0f, 0.0f ,  0.0f , 1.0f , 1.0f , 0.1f,0.0f };
float blue_color[] = { 0.5f, 0.0f , 0.5f , 0.5f , 0.0f, 0.0f , 0.1f };
float green_color[] = { 1.0f, 1.0f , 0.5f , 0.0f ,1.0f , 0.0f ,0.0f };


float carousel_rot = 90;
float carousel_rot_b = 90;
float carousel_rot_c = 90;
float planets_rot = 90;
double pos = 0;

// Our Rendering Is Done Here
void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Do we have culling enabled?
	if (b_culling == true)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);


	//day to night
	if (gray) {
		glClearColor(day_to_night += 0.0008, day_to_night += 0.0008, day_to_night += 0.0008, 1.f);
		if (day_to_night >= 0.9)
			gray = !gray;
	}
	else {
		glClearColor(day_to_night -= 0.0008, day_to_night -= 0.0008, day_to_night -= 0.0008, 1.0f);
		if (day_to_night <= 0)
			gray = !gray;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer



	glPushMatrix();

	glRotatef(planets_rot -= 0.50, 0, 0, 1); //speed of  the sun and the moon 

	//moon
	glTranslatef(10, 2, 0); //place the moon above
	draw_moon(); //create the monn

	//sun
	glTranslatef(-20, -2, 0); //place the sun below
	draw_sun();//create the sun 

	//light from the sun 
	GLfloat light_position_sun_specualr[] = { 1.0,1.0,1.0, 1.0 };
	GLfloat light_position_sun[] = { planets_rot,0,1.0, 1.0 }; //position of the sun
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_position_sun_specualr);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position_sun);
	glEnable(GL_LIGHT2);



	glPopMatrix();


	glPushMatrix();
	glScalef(0.8, 0.8, 1);

	//red flag
	glPushMatrix();

	glScalef(0.8, 0.8, 1);
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red color

	glTranslatef(0, 11.1, 0.0);
	glRotatef(+90, -6.0, 70.0, 0.0);

	glutSolidCone(0.5, 2.7, 20.0, 20.0);


	glPopMatrix();

	//glTranslatef(-1.9, 0.0, 2.5);


	//base of flag
	glPushMatrix();
	glScalef(0.8, 0.8, 1);
	glTranslatef(0, 9.0, 0.0);
	glRotatef(-70, 1.0, 0.0, 0.0);
	cylinder(2.5, 0.1, 0.0f, 0.0f, 1.0f); //cylinder for the flag
	glPopMatrix();


	//upper part 

	glPushMatrix(); //push for the carousel

	//cone
	glPushMatrix();
	glScalef(0.8, 0.8, 1);
	glColor3f(0.0f, 0.5f, 1.0f);//baby Blue

	glTranslatef(0, 4.9, 1.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glutSolidCone(7.8, 4.0, 20.0, 20.0);//creating a cone for the top part 
	glPopMatrix();



	//upper cylider 

	glPushMatrix();

	glScalef(0.8, 0.8, 1);
	glColor3f(1.0f, 1.0f, 1.0f);

	glRotatef(carousel_rot += 0.2, 0.0, 1.0, 0.0); //rotation of  the uppert part of the carousel
	glTranslatef(0.0, 5.0, 0.0);
	glRotatef(-90.0, -1.0, 0.0, 0.0);
	cylinderB(1.0, 8.0, 240, 248, 255); // cylinder of the top part



	glPopMatrix();



	//bottom part

	glRotatef(carousel_rot_b += 0.5, 0.0, 1.0, 0.0); //rotation of the main carousel part


	glTranslatef(0.0, -3, 0);
	glRotatef(-90, 1.0, 0.0, 0.0); // change angle of cylinders
	cylinder(7.0, 2.0, 0.5f, 1.0f, 1.0f); // middle part of carousel
	//glRotatef(-80, 1.0, 0.0, 0.0); // change angle of cylinders
	cylinderB(1.0, 6.0, 0, 0, 0); //base of carousel


	//Creating 6 animals
	for (int i = 1; i <= 6; i++) {
		float r = 5.0;


		glPushMatrix();

		glScalef(0.8, 0.8, 1);

		float angle_x = r * sin(i);
		float angle_y = r * cos(i);

		glTranslatef(angle_x, angle_y, 0); // make the small cyclinders of the horses to be around the centre cyclinder
		cylinderforPony(7.0, 0.2, 0.0f, 0.5f, 1.0f); //creating the smallest cylinders for the animals , color baby blue
		glTranslatef(0.0, 0, 1.75); // in the middle of the cylinder

		glTranslatef(0, 0, sin((pos += .005) + i * 45)); // movement with sin way

		glRotatef(-45 - (i - 1) * (60), 0, 0, 1); //initials positions


		if (i % 2 == 0) {

			creating_pony(i, red_color[i - 1], blue_color[i - 1], green_color[i - 1]); //creating a pony
		}
		else {

			creating_cats(i, red_color[i - 1], blue_color[i - 1], green_color[i - 1]); //creating a cat
		}


		glPopMatrix();

	}
	glPopMatrix();




	glPopMatrix(); //pop for scale

	glutSwapBuffers();
	glutPostRedisplay(); //animation
}