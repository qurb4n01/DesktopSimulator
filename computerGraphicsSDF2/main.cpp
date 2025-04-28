#include <GL/glut.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>


std::vector<std::string> terminalOutputLines;
std::vector<std::string> chromeOutputLines;

int window_width = 800;
int window_height = 600;


std::string calcInput = "";
std::string calcResult = "";

std::string inputBuffer = "";
std::string chromeInput = "";
bool chromeIsActive = false;
std::string chromeOutput = "";


void run_ls();
void run_cd(const std::string& dir);
void run_cat(const std::string& filename);
void run_chrome();


struct AppIcon {
    float x, y, size;
    std::string name;
    bool is_open;
};

AppIcon icons[] = {
    {100, 500, 64, "CMD", false},
    {200, 500, 64, "Calc", false},
    {300, 500, 64, "Chrome", false}
};

struct File {
    std::string name;
    std::string content;
};

struct Folder {
    std::string name;
    std::vector<File> files;
    std::vector<Folder*> subfolders;
    Folder* parent = nullptr;
};

Folder root;
Folder* currentDir;
std::vector<std::string> terminalOutput;



void drawRect(float x, float y, float w, float h) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}


void drawText(float x, float y, std::string text) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}


std::vector<std::string> splitTextIntoLines(const std::string& text, int maxLineWidth) {
    std::vector<std::string> lines;
    std::string currentLine;

    for (char c : text) {
        currentLine += c;
        if (currentLine.size() >= maxLineWidth) {
            lines.push_back(currentLine);
            currentLine.clear();
        }
    }


    if (!currentLine.empty()) {
        lines.push_back(currentLine);
    }

    return lines;
}



void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();


    glColor3f(0.6f, 0.8f, 1.0f);
    drawRect(0, 0, window_width, window_height);


    for (int i = 0; i < 3; i++) {
        AppIcon& app = icons[i];
        glColor3f(0.2f, 0.2f, 0.5f);
        drawRect(app.x, app.y, app.size, app.size);
        glColor3f(1, 1, 1);
        drawText(app.x, app.y - 20, app.name);
    }


    if (icons[0].is_open) {
        glColor3f(0.0f, 0.0f, 0.0f);
        drawRect(150, 150, 500, 300);


        glColor3f(1.0f, 0.0f, 0.0f);
        drawRect(630, 420, 20, 20);
        glColor3f(1, 1, 1);
        drawText(635, 425, "X");


        glColor3f(0.0f, 1.0f, 0.0f);
        int lineY = 430;
        for (size_t i = 0; i < terminalOutput.size() && lineY > 160; ++i) {
            drawText(160, lineY, terminalOutput[i]);
            lineY -= 20;
        }
        drawText(160, 160, "qurban_rauf@Sinux:~$ " + inputBuffer);
    }


    if (icons[1].is_open) {
        glColor3f(0.1f, 0.1f, 0.1f);
        drawRect(150, 150, 500, 300);


        glColor3f(1.0f, 0.0f, 0.0f);
        drawRect(630, 420, 20, 20);
        glColor3f(1, 1, 1);
        drawText(635, 425, "X");


        glColor3f(1.0f, 1.0f, 1.0f);
        drawText(160, 420, "Calculator");

        drawText(160, 380, "Expression: " + calcInput);
        drawText(160, 340, "Result: " + calcResult);


        glColor3f(0.0f, 0.5f, 1.0f);
        int clearButtonX = 150 + 200;
        int clearButtonY = 170;
        int clearButtonWidth = 100;
        int clearButtonHeight = 30;

        drawRect(clearButtonX, clearButtonY, clearButtonWidth, clearButtonHeight);
        glColor3f(1, 1, 1);
        drawText(clearButtonX + 25, clearButtonY + 10, "CLEAR");
    }


    if (icons[2].is_open) {
        glColor3f(0.0f, 0.0f, 0.0f);
        drawRect(150, 150, 500, 300);


        glColor3f(1.0f, 0.0f, 0.0f);
        drawRect(630, 420, 20, 20);
        glColor3f(1, 1, 1);
        drawText(635, 425, "X");


        glColor3f(1.0f, 1.0f, 1.0f);
        drawText(160, 370, "Enter URL: " + chromeInput);


        int startY = 320;
        for (size_t i = 0; i < chromeOutputLines.size(); ++i) {
            drawText(160, startY - (i * 20), chromeOutputLines[i]);
        }
    }

    glutSwapBuffers();
}



void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        int correctedY = window_height - y;


        for (int i = 0; i < 3; i++) {
            AppIcon& app = icons[i];
            if (x >= app.x && x <= app.x + app.size &&
                correctedY >= app.y && correctedY <= app.y + app.size) {
                if (app.name == "CMD") {
                    app.is_open = true;
                    inputBuffer = "";
                } else if (app.name == "Calc") {
                    app.is_open = true;
                    calcInput = "";
                    calcResult = "";
                } else if (app.name == "Chrome") {
                    app.is_open = true;
                    chromeIsActive = true;
                    chromeInput = "";
                    chromeOutput = "";
                }
            }
        }


        if (icons[0].is_open && x >= 630 && x <= 650 && correctedY >= 420 && correctedY <= 440) {
            icons[0].is_open = false;
        }


        if (icons[1].is_open) {

            if (x >= 630 && x <= 650 && correctedY >= 420 && correctedY <= 440) {
                icons[1].is_open = false;
            }


            int clearButtonX = 350;
            int clearButtonY = 170;
            int clearButtonWidth = 100;
            int clearButtonHeight = 30;

            if (x >= clearButtonX && x <= clearButtonX + clearButtonWidth &&
                correctedY >= clearButtonY && correctedY <= clearButtonY + clearButtonHeight) {
                calcInput = "";
                calcResult = "";
            }
        }


        if (icons[2].is_open && x >= 630 && x <= 650 && correctedY >= 420 && correctedY <= 440) {
            icons[2].is_open = false;
            chromeIsActive = false;
        }

        glutPostRedisplay();
    }
}

std::string calculate(const std::string& expr) {
    double num1 = 0, num2 = 0;
    char op = 0;
    std::istringstream iss(expr);

    iss >> num1 >> op >> num2;

    double result = 0;
    if (op == '+') result = num1 + num2;
    else if (op == '-') result = num1 - num2;
    else if (op == '*') result = num1 * num2;
    else if (op == '/') {
        if (num2 == 0) return "Error: Divide by 0";
        result = num1 / num2;
    }
    else return "Invalid";

    std::ostringstream oss;
    oss << result;
    return oss.str();
}

void keyboard(unsigned char key, int x, int y) {
    if (icons[0].is_open) {
        if (key == 13) {
            terminalOutput.push_back("qurban_rauf@Sinux:~$ " + inputBuffer);

            std::istringstream iss(inputBuffer);
            std::string command;
            iss >> command;

            if (command == "ls") {
                run_ls();
            } else if (command == "cd") {
                std::string dir;
                iss >> dir;
                run_cd(dir);
            } else if (command == "cat") {
                std::string file;
                iss >> file;
                run_cat(file);
            } else if (command == "whoami") {
                terminalOutput.push_back("root");
            } else {
                terminalOutput.push_back("Command not found: " + command);
            }

            inputBuffer.clear();
            glutPostRedisplay();
        } else if (key == 8) {
            if (!inputBuffer.empty())
                inputBuffer.pop_back();
        } else {
            inputBuffer += key;
        }

        glutPostRedisplay();
    }


    if (icons[2].is_open && chromeIsActive) {
        if (key == 13) {
            if (chromeInput == "github.com") {
                chromeOutput = "GitHub Account: qurb4n01";
            } else if (chromeInput == "hacibenqbenq.com") {
                chromeOutput = "This website is banned from internet. If you want to contact us for more information, call 055-583-92-14. Muveqqeti narahatciliga gore uzr isteyirik ~mudiriyyet HaciBenqBenq ASC";
            } else {
                chromeOutput = "404 Not Found";
            }


            int maxLineWidth = 40;
            chromeOutputLines = splitTextIntoLines(chromeOutput, maxLineWidth);

            chromeInput = "";
            glutPostRedisplay();
        } else if (key == 8) {
            if (!chromeInput.empty())
                chromeInput.pop_back();
        } else {
            chromeInput += key;
        }

        glutPostRedisplay();
    }

    if (icons[1].is_open) {

        if (key == 13) {
            calcResult = calculate(calcInput);
        } else if (key == 8) {
            if (!calcInput.empty()) calcInput.pop_back();
        } else {
            calcInput += key;
        }
        glutPostRedisplay();
    }
}






void run_ls() {
    std::string out = "";
    for (const auto& f : currentDir->files) {
        out += f.name + "  ";
    }
    for (const auto& folder : currentDir->subfolders) {
        out += folder->name + "/  ";
    }
    terminalOutput.push_back(out.empty() ? "[empty]" : out);
}


void run_cd(const std::string& dir) {
    if (dir == ".." && currentDir->parent) {
        currentDir = currentDir->parent;
        return;
    }

    for (auto& folder : currentDir->subfolders) {
        if (folder->name == dir) {
            currentDir = folder;
            return;
        }
    }

    terminalOutput.push_back("No such directory: " + dir);
}


void run_cat(const std::string& filename) {
    for (auto& file : currentDir->files) {
        if (file.name == filename) {
            terminalOutput.push_back(file.content);
            return;
        }
    }
    terminalOutput.push_back("File not found: " + filename);
}


void setup2D() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, window_width, 0, window_height);
    glMatrixMode(GL_MODELVIEW);
}


void initFileSystem() {
    root.name = "/";
    currentDir = &root;

    Folder* desktop = new Folder{"Desktop", {}, {}, &root};
    desktop->files.push_back({"flag.txt", "CTF{qurb4n_r4uf_15_b41}"});

    Folder* documents = new Folder{"Documents", {}, {}, &root};
    documents->files.push_back({"resume.txt", "Gurban Bannayev - CV - 2025"});

    Folder* downloads = new Folder{"Downloads", {}, {}, &root};
    downloads->files.push_back({"setup.exe", "This is a virus, do not execute!"});

    root.subfolders.push_back(desktop);
    root.subfolders.push_back(documents);
    root.subfolders.push_back(downloads);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("Desktop Simulator");

    initFileSystem();

    glClearColor(0.9f, 0.9f, 1.0f, 1.0f);
    setup2D();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
