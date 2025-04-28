# DesktopSimulator
___________________________________________________________________
Comp Grap SDF2

## Proyektin adi: Desktop Simulator
## Emeliyyat sistemimizin adi: Sinux (Sinus+Linux)
## Hazirlayanlar: Qurban Bennayev ve Rauf Celilov 

proyekt Desktop Simulatordur, basic dille kompyuter icinde kompyuter. yapay Desktopumuzun icinde 3app var: CMD, Calc, Chrome. CMDde cd,ls,cat,whoami kimi komandalar calisdirma olur. Calculatorda + - * / kimi operatorlar calistirmaq olur. Chromeda 2 "sayta" getmek olur: GitHub.com ve hacibenqbenq.com. proyekt qisa olaraq overview bu qeder, indi ise koddaki funksiyalar ne ise yariyir onlari izah edecem:

___
drawRect() draws a filled rectangle in 2D space using OpenGL,  
where:
(x, y) is the bottom-left starting point,
w is the width,
h is the height.
It connects four points in counter-clockwise order to form a filled shape.
bunu Desktopdaki cmd,chrome ve calc obyektlerini draw etmek ucun yazdim
___

drawText() draws a text string onto the screen at the given (x, y) position,
character by character, using a bitmap font (Helvetica 18 size).
OpenGL doesn't have text drawing by default, so GLUT provides simple bitmap fonts. This function manually draws each character next to the previous one.
bunu cmd,chrome ve calcda yazi yazmaq ucun yazdim
___

splitTextIntoLines() takes a big text string
Cuts it into multiple smaller lines,
Each line has at most maxLineWidth characters.
It basically formats long text into a list of shorter lines so you can display it nicely without the text overflowing or running too wide.
bunu chromeda text box dan kenara cixmasin deye yazdim
___

The display() function is used to render the graphical interface of a window with multiple interactive components, such as:
Background: Clears the screen and renders a background rectangle (light blue).
Icons: Draws 3 app icons (terminal, calculator, and browser) on the screen. Each icon is drawn with its respective position and name.
Terminal Window (if open): If the terminal is open, it displays a black window with terminal output and a prompt. A close button ("X") is also rendered in the top-right corner.
Calculator Window (if open): If the calculator is open, it renders a gray window displaying the current expression, result, and a "CLEAR" button.
Browser Window (if open): If the browser is open, it renders a black window with an input for a URL and the output displayed below.
Text Rendering: Displays texts like app names, terminal output, calculator expressions, and browser content, making sure that everything fits within the window boundaries.
Buffer Swap: Finally, it swaps the buffers to display the rendered frame.
___

The mouse() function handles mouse events (specifically mouse clicks) in a graphical user interface (GUI) created using OpenGL and GLUT. It allows the user to interact with different application icons and perform actions such as opening, closing, and interacting with apps (CMD, Calculator, and Chrome). The function is designed to manage the state of these apps based on where and what the user clicks in the window. Here's a breakdown of its overall flow:
Mouse Button Down Detection:
The function starts by checking if the mouse button is pressed down (state == GLUT_DOWN). This ensures that actions are triggered only when the user clicks the mouse button.
Correcting Y-Coordinate:
This ensures that the mouse click's y coordinate is interpreted correctly in the context of OpenGL's coordinate system.
Icon Click Detection and App Opening:
The function checks if the user clicked on one of the application icons (CMD, Calculator, or Chrome). It does this by checking if the mouse click coordinates (x, correctedY) lie within the bounding box of any of the icons. If the user clicks on an icon, the corresponding app is opened by setting its is_open flag to true, and any relevant input fields are reset to their initial state.
Close Button Click Detection:
The function also handles the closing of open applications. For each application (CMD, Calculator, and Chrome), it checks if the user clicks the close button (the "X" in the corner of the app window). If the user clicks the close button, the app is closed by setting its is_open flag to false.
Calculator "Clear" Button Detection:
In addition to closing the Calculator, the function checks if the user clicks the "CLEAR" button within the Calculator app. If clicked, the input and result fields of the Calculator are cleared.
Redrawing the Window:
After handling all the mouse click events, the function calls glutPostRedisplay(). This triggers the window to be redrawn, reflecting the updated state of the application, such as whether the apps are open or closed and whether the inputs have been cleared.
___

The calculate() function is designed to evaluate simple mathematical expressions (addition, subtraction, multiplication, division) provided as strings. It extracts the operands and operator from the string, performs the calculation, and returns the result as a string. It also handles errors like division by zero and invalid operators gracefully.
___

The keyboard() function listens for keyboard events and updates the application based on which "app" (CMD, Calculator, or Chrome) is currently active.
For the CMD app, it processes shell-like commands, executes them, and displays the output.
For the Chrome app, it simulates browsing, providing fixed responses to specific inputs.
For the Calculator app, it processes mathematical expressions and displays the results.
After each input event (whether a command or key), the display is updated by calling glutPostRedisplay().
___

run_ls(): Lists the files and subdirectories of the current directory. It uses the files and subfolders vectors from the currentDir object.
run_cd(const std::string& dir): Changes the current directory to the specified folder, or moves to the parent directory if ".." is provided. If the directory does not exist, an error message is shown.
run_cat(const std::string& filename): Displays the content of a specified file in the current directory. If the file is not found, it shows an error message.
___

The setup2D() function configures OpenGL to use a 2D orthogonal projection.
It sets the projection matrix to an identity matrix, then defines the 2D coordinate system (with the origin at the bottom-left corner).
It finally switches back to the modelview matrix for further transformations related to the objects themselves.
___

The initFileSystem() function initializes a simple in-memory file system with the following structure:
/ (Root)
  ├── Desktop
  │     └── flag.txt ("CTF{qurb4n_r4uf_15_b41}")
  ├── Documents
  │     └── resume.txt ("Gurban Bannayev - CV - 2025")
  └── Downloads
        └── setup.exe ("This is a virus, do not execute!")
It creates the root directory and three subdirectories: Desktop, Documents, and Downloads.
Each folder has a few files with predefined content, and the root directory holds references to these subfolders.
This setup mimics a simple file system where users can navigate between directories and view or edit files.
___

main() function follows the standard pattern for small OpenGL/GLUT applications.
___




Funksiyalar olan hisse sona catdi indi ise kodda geride qalan digerleri ne is gorur onlari qisa olaraq yazacam:


## include lines:
GL/glut.h: Provides OpenGL/GLUT functions (for window, drawing, input, etc.)
iostream: For input/output with std::cout, etc.
string: To use std::string for text.
vector: To use std::vector, a dynamic array (resizable list).
sstream: To split strings into pieces easily (std::istringstream).


## Global Variables:
```cpp
std::vector<std::string> terminalOutputLines;
std::vector<std::string> chromeOutputLines;
```
terminalOutputLines → what gets printed in your command line output.
chromeOutputLines → used for simulating webpage display output, especially when it's too long.


## Window Size:
```cpp
int window_width = 800;
int window_height = 600;
```

## Calculator Variables:
```cpp
std::string calcInput = "";
std::string calcResult = "";
```
calcInput: What the user is typing into the calculator.
calcResult: The result of the calculation after pressing Enter.


## Terminal and Chrome Inputs:
```cpp
std::string inputBuffer = "";
std::string chromeInput = "";
bool chromeIsActive = false;
std::string chromeOutput = "";
```
inputBuffer: Stores what the user types in the CMD/Terminal app.
chromeInput: Stores what the user types in the Chrome address bar.
chromeIsActive: A flag to indicate if Chrome input is currently being typed.
chromeOutput: What Chrome should display after loading the page (github account, 404, banned site, etc.)


## Function Declarations:
```cpp
void run_ls();
void run_cd(const std::string& dir);
void run_cat(const std::string& filename);
void run_chrome();
```
run_ls(): Lists files/folders.
run_cd(dir): Changes the directory.
run_cat(filename): Displays file contents.
run_chrome(): (You declared it, but not shown yet — maybe you planned a separate function for Chrome behavior).


## Structures:
```cpp
struct AppIcon {
    float x, y, size;
    std::string name;
    bool is_open;
}
```
x, y: Position on the screen.
size: Size (width/height) of the icon.
name: App's name (e.g., "CMD", "Calc", "Chrome").
is_open: Whether the app is currently open (clicked).


## App icons array:
```cpp
AppIcon icons[] = {
    {100, 500, 64, "CMD", false},
    {200, 500, 64, "Calc", false},
    {300, 500, 64, "Chrome", false}
};
```
Purpose: Create 3 icons on the desktop.
Explanation:
CMD (Terminal) at (100,500),
Calc (Calculator) at (200,500),
Chrome at (300,500).
They all start closed (is_open = false).


## File:
```cpp
struct File {
    std::string name;
    std::string content;
};
```
Purpose: Represents a file (filename + what's inside it).
Fields:
name: Name of the file (e.g., "flag.txt").
content: The file's actual text content.


## Folder:
```cpp
struct Folder {
    std::string name;
    std::vector<File> files;
    std::vector<Folder*> subfolders;
    Folder* parent = nullptr;
};
```
Purpose: Represents a folder (directory) in your file system.
Fields:
name: Folder name (e.g., "Desktop").
files: List of files inside the folder.
subfolders: List of pointers to its subfolders.
parent: Pointer to the folder's parent (helps with cd .. command).


## Root and Current Directory:
```cpp
Folder root;
Folder* currentDir;
std::vector<std::string> terminalOutput;
```
root:
The "root" directory /.
Everything (Desktop, Documents, Downloads) is a subfolder of this.
currentDir:
Pointer to where the user currently is.
Initially points to root.
terminalOutput:
Stores command-line outputs as a series of strings (each time you type a command like ls, cd, etc.).

____________________________________________________________________

