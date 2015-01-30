#include "appView.h"


AppView::AppView(AppController *newAppController, AppModel *newAppModel) {
  // init variables
  appController = newAppController; 
  appModel = newAppModel;
  
  frame = 0;
  width = 800; height = 600;
  windowTitle = "3D Calendar Visualisation";
  prototype_name = "Prototype 1: Flat perspective view";
  name_size = strlen(prototype_name);

  // assign a default value
  MENU_TYPE show = MENU_1;

}

void AppView::init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
}

void AppView::display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  double aspect = (double)viewport[2] / (double)viewport[3];
  gluPerspective(60, aspect, 1, 100);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // update frame
  frame++;

  // move back a bit
  glTranslatef(0, 0, 0+pos_z);

  // draw objects
  calendar.draw(frame);
  
  // vertical axis
  glBegin(GL_LINES);
    glColor3f(0,1,0);
    glVertex3f(0, 1000, -10);
    glVertex3f(0,-1000, -10);
  glEnd();
  // horizontal axis
  glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(1000, 0, -10);
    glVertex3f(-1000,0, -10);
  glEnd();


  // draw text
  calendar.drawText(0, 0, "CALENDAR VISUALISATION PROTOTYPE");
  calendar.drawText(width*(0.5f)-name_size*(10*0.5), height-10, prototype_name);

  glutSwapBuffers();
}

void AppView::reshape(int w, int h) {
  glViewport(0, 0, w, h);
}

void AppView::timer(int extra) {
  glutPostRedisplay();
  glutTimerFunc(16, timerWrapper, 0);
}

void AppView::menu(int item) {
  switch (item) {
    case MENU_1:
      calendar.setPrototype(1);
      prototype_name = "Prototype 1: Flat perspective view";
      reset();
      break;
    case MENU_2:
      calendar.setPrototype(2);
      prototype_name = "Prototype 2: Time tunnel view";
      reset();
      break;
    case MENU_3:
      calendar.setPrototype(3);
      prototype_name = "Prototype 3: 3D Fibonacci spiral";
      reset();
      break;
    case MENU_4:
      calendar.setPrototype(4);
      prototype_name = "Prototype 4: ";
      reset();
      break;
    default:
      break;
   }

  glutPostRedisplay();
  return;
}

void AppView::mouse(int button, int state, int x, int y) {
  // Wheel reports as button 3(scroll up) and button 4(scroll down)
  if ((button == 3) || (button == 4)) // It's a wheel event
  {
    // Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
    if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
     
    // scroll wheel actions
    if(button == 3) { // scroll up
      pos_z += 0.25f;
    } else {          // scroll down
      pos_z -= 0.25f;
    }
    glutSwapBuffers();

  } else {  // normal button event
    printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
  }
}

// void method access via wrapper
AppView *AppView::instance = NULL;

void AppView::displayWrapper() {
  instance->display();
}

void AppView::reshapeWrapper(int w, int h) {
  instance->reshape(w,h);
}

void AppView::timerWrapper(int extra) {
  instance->timer(extra);
}

void AppView::menuWrapper(int item) {
  instance->menu(item);
}

void AppView::mouseWrapper(int button, int state, int x, int y) {
  instance->mouse(button, state, x, y);
}

void AppView::setInstance() {
  instance = this;
}

// public methods
int AppView::start(int argc, char *argv[]) {
  
  setInstance();

  // init glut
  glutInit(&argc, argv);
  glutInitWindowSize(width, height);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow(windowTitle);

  glutDisplayFunc(displayWrapper);
  glutReshapeFunc(reshapeWrapper);
  glutTimerFunc(0, timerWrapper, 0);

  // Create a menu
  glutCreateMenu(menuWrapper);
 
  // Add menu items
  glutAddMenuEntry("Prototype 1", MENU_1);
  glutAddMenuEntry("Prototype 2", MENU_2);
  glutAddMenuEntry("Prototype 3", MENU_3);
  glutAddMenuEntry("Prototype 4", MENU_4);

  // Associate a mouse button with menu
  glutAttachMenu(GLUT_RIGHT_BUTTON); 

  // add mouse listener
  glutMouseFunc(mouseWrapper); 
  
  init();
  glutMainLoop();

  return 0;
}

void AppView::setWindowSize(int w, int h) {
  width = w;
  height = h;
}

void AppView::setWindowTitle(char* title) {
  windowTitle = title;
}

void AppView::reset() {
  name_size = strlen(prototype_name);
  pos_z = 0;
}