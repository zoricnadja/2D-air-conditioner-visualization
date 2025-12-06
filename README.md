
# 2D Air Conditioner Simulation – OpenGL 3.2  
**Course:** Computer Graphics  
**Program:** Software Engineering and Information Technologies (2025)  

---

## Project Description  
This project is a **2D graphical simulation of an air conditioning unit**, developed as part of the *Computer Graphics* course in the Software Engineering and Information Technologies program.  
The application demonstrates key OpenGL concepts using **OpenGL 3.2 with a programmable pipeline**.  

---

## Features & Requirements  
- **OpenGL 3.2 programmable pipeline**  
- **Shaders programming** (vertex & fragment shaders)  
- **Uniforms, transparency, and/or textures**  
- **Mouse and keyboard input**  
- **Custom cursor** (remote control image with laser in the top-left corner)  
- **Frame limiter at 75 FPS**  
- **Full-screen mode**  
- **Exit on ESC key**  
- **Semi-transparent texture with student name, surname, and index in a corner**  

---

## Application Behavior  
### Initial State  
- AC is off, lamp is off, vent closed, screens black  

### Turn On  
- Left-click on the lamp → lamp turns red, vent opens at constant speed, screens activate  
- **Screen 1:** Desired temperature (default 24°C)  
- **Screen 2:** Measured temperature (default 30°C)  
- **Screen 3:** Icon (🔥 fire if desired > measured, ❄ snowflake if desired < measured, ✅ checkmark if equal)  
- Measured temperature gradually adjusts to desired temperature  

### Controls  
- **↑ Arrow:** Increase desired temperature by 1°C  
- **↓ Arrow:** Decrease desired temperature by 1°C  
- **Space:** Empty basin (reset water level)  

### Water Simulation  
- Basin fills with light-blue rectangle every second  
- If basin is full → AC turns off automatically and cannot restart until emptied  

### Turn Off  
- Left-click on lamp or basin overflow → lamp and screens off, vent closes  

---

## Technologies Used  
- **Language:** C++  
- **Graphics:** OpenGL 3.2  
- **Libraries:** GLFW / FreeType (for text rendering)  

---

## How to Run  
1. Clone the repository:  
2. Build the project using your preferred IDE or CMake.
3. Run the executable in full-screen mode.
