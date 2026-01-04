//https://github.com/Gchipunov/gchipunov.github.io/new/main/QuatCamera
// https://www.krikey.ai/3d-animation-editor
// https://www.youtube.com/watch?v=by53T03Eeds


//#include "quat_camera.h"
#include "QuatCamera.h"

ColoQuatCamera::ColoQuatCamera(int width, int height, GLFWwindow* Mainwindow)
{
    //forced camera place, after fixed view matrix being multipled:
    // 0.220146
    // 0.827904
    // 0.397505

    //yaw 1.820002
    // pitch:-0.535398

    //0.000000, y: -1.600000, z: -54.399742 y: -12.220046, p: 3.177385

//g_ColoQuatCamera.x: 0.000000, y: -1.600000, z: -54.399742 y: -12.240047, p: 3.172384


    //	Vec3 position = Vec3(-5, -5, 4);
        //	Vec3 position = Vec3( 0.5,  0.5, 1.0);
    //	Vec3 position = Vec3( 0.220146f,  0.827904f, 10.0f);

    //	Vec3 position = Vec3(-5,40.0f, 4);
    //Vec3 position = Vec3(0.0f,40.0f, -4);
    // position = Vec3(0.0f,40.0f, -4);

    // g_ColoQuatCamera.x: 546.000000, y: 384.000000, z: 0.000000
//	position = Vec3(546.0f, 384.0f, 0.0f);
    // position = Vec3((float)width/ 2.0f, (float)height/ 2.0f, -10.0f);

    Quaternion orientation;

    // pitch = 0.0f;
    pitch = -M_PI / 4.0f;
    //yaw = 2.3;
   // yaw = -M_PI / 2.0f; //0.0f;
    yaw = M_PI / 2.0f;
    //g_ColoQuatCamera.x: 0.100000, y: 4.499998, z: 139.699326 y: 1.596024, p: 0.029689
   // position = Vec3(0.100000f, 4.499998f, 139.699326f);
    position = Vec3(0.100000f, 0.199998f, 139.699326f);

    // yaw= -( M_PI  / 2.0f);//last1
     // pitch = M_PI  / 10.0f;
    // roll = M_PI  / 2.0f;
    // roll = 0.0f;//last1
     // roll = M_PI / 4.0f;
    //  pitch = 0.3f;  //last1
      // g_ColoQuatCamera.x:
// 0.100000, y: 0.199998, z: 139.699326 y: -1.978796, p: -0.001000, r: 0.000000
    yaw = -1.978796f;
    pitch = -0.0f;
    roll = 0.0f;

    // new values 1:
  //  g_ColoQuatCamera.x:
  // -92.899155, y: -181.901917, z: 138.899277 y: -0.007798, p: 0.393500, r: -0.919999

  // new values 2:
  // g_ColoQuatCamera.x:
  // -100.399040, y: 0.199998, z: 139.699326 y: -0.038795, p: 0.632000, r: 0.000000
    position = Vec3(-100.100000f, 0.199998f, 139.699326f);

    position = Vec3(0.00000f, 0.00f, 0.00f);

    yaw = 0.0f;
    pitch = M_PI / 5.0f;;
    roll = 0.0f;
    // 

 //g_ColoQuatCamera.x:
 // -98.700020, y: 0.699998, z: 136.399124 y: -0.001000, p: 0.635819, r: 0.000000


    moveSpeed = 5.0f;
    // rotateSpeed = 0.005f;// way too fast even to debug in radians,, might be okish for degrees
    rotateSpeed = 0.0005f; // save
    //rotateSpeed = 0.00005f;


        // World constants
    WORLD_UP = Vec3(0, 0, 1); // Z is up!
    WORLD_FORWARD = Vec3(0, 1, 0);
    WORLD_RIGHT = Vec3(1, 0, 0);

    // Set initial orientation
    updateCameraOrientation();

    perpective = Mat4();
    view = Mat4();

    m_iWidth = width;
    m_iHeight = height;
    window = Mainwindow;


}
ColoQuatCamera::~ColoQuatCamera()
{

}
/*
    void ColoQuadCamera::update(float deltaTime) {
        const moveAmount = camera.moveSpeed * deltaTime;

        // Calculate camera direction vectors from orientation
        const forwardDir = vec3.create();
        vec3.transformQuat(forwardDir, WORLD_FORWARD, camera.orientation);

        const rightDir = vec3.create();
        vec3.transformQuat(rightDir, WORLD_RIGHT, camera.orientation);
        const upDir = vec3.create();
        vec3.transformQuat( upDir, WORLD_UP, camera.orientation);
        // --- Handle Movement ---
        if (inputState.keys['forward']) { // Move Forward
            const move = vec3.scale(vec3.create(), forwardDir, moveAmount);
            vec3.add(camera.position, camera.position, move);
        }
        if (inputState.keys['backward']) { // Move Backward
            const move = vec3.scale(vec3.create(), forwardDir, -moveAmount);
            vec3.add(camera.position, camera.position, move);
        }
        if (inputState.keys['left']) { // Strafe Left
            const move = vec3.scale(vec3.create(), rightDir, -moveAmount);
            vec3.add(camera.position, camera.position, move);
        }
        if (inputState.keys['right']) { // Strafe Right
            const move = vec3.scale(vec3.create(), rightDir, moveAmount);
            vec3.add(camera.position, camera.position, move);
        }

      if (inputState.keys['up']) { // Move Forward
            const move = vec3.scale(vec3.create(), upDir, moveAmount);
            vec3.add(camera.position, camera.position, move);
        }
        if (inputState.keys['down']) { // Move Backward
            const move = vec3.scale(vec3.create(), upDir, -moveAmount);
            vec3.add(camera.position, camera.position, move);
        }
    }
    */
    /**
 * @brief Updates the camera's position based on input state and delta time.
 * @param deltaTime The time elapsed since the last frame, in seconds.
 */
void ColoQuatCamera::update(float deltaTime) {
    // Calculate the amount of movement for this frame.
    const float moveAmount = this->moveSpeed * deltaTime;

    // Calculate camera direction vectors from orientation by transforming
    // the world vectors with the camera's orientation quaternion.
    Vec3 forwardDir = transform(this->WORLD_FORWARD, this->orientation);
    Vec3 rightDir = transform(this->WORLD_RIGHT, this->orientation);
    Vec3 upDir = transform(this->WORLD_UP, this->orientation);

    // --- Handle Movement ---
    if (this->inputState.keys.count("forward") && this->inputState.keys["forward"]) {
        // Move Forward
        this->position = this->position + forwardDir * moveAmount;
    }
    if (this->inputState.keys.count("backward") && this->inputState.keys["backward"]) {
        // Move Backward
        this->position = this->position + forwardDir * (-moveAmount);
    }
    if (this->inputState.keys.count("left") && this->inputState.keys["left"]) {
        // Strafe Left
        this->position = this->position + rightDir * (-moveAmount);
    }
    if (this->inputState.keys.count("right") && this->inputState.keys["right"]) {
        // Strafe Right
        this->position = this->position + rightDir * moveAmount;
    }

    if (this->inputState.keys.count("up") && this->inputState.keys["up"]) {
        // Move Up
        this->position = this->position + upDir * moveAmount;
    }
    if (this->inputState.keys.count("down") && this->inputState.keys["down"]) {
        // Move Down
        this->position = this->position + upDir * (-moveAmount);
    }
    updateCameraMatrixes();

}

void ColoQuatCamera::updateDebug(float deltaTime) {
    // Calculate the amount of movement for this frame.
    const float moveAmount = this->moveSpeed * deltaTime;

    // Calculate camera direction vectors from orientation by transforming
    // the world vectors with the camera's orientation quaternion.
    Vec3 forwardDir = transform(this->WORLD_FORWARD, this->orientation);
    Vec3 rightDir = transform(this->WORLD_RIGHT, this->orientation);
    Vec3 upDir = transform(this->WORLD_UP, this->orientation);

    // --- Handle Movement ---
    if (this->inputState.keys.count("forward2") && this->inputState.keys["forward2"]) {
        // Move Forward
        this->position.x = this->position.x + 1.0f;//this->position + forwardDir * moveAmount;
    }
    if (this->inputState.keys.count("backward2") && this->inputState.keys["backward2"]) {
        // Move Backward
        this->position.x = this->position.x - 1.0f;// this->position + forwardDir * (-moveAmount);
    }
    if (this->inputState.keys.count("left2") && this->inputState.keys["left2"]) {
        // Strafe Left
        this->position.y = this->position.y - 1.0f;// this->position + rightDir * (-moveAmount);
    }
    if (this->inputState.keys.count("right2") && this->inputState.keys["right2"]) {
        // Strafe Right
      //  this->position = this->position + rightDir * moveAmount;
        this->position.y = this->position.y + 1.0f;
    }

    if (this->inputState.keys.count("up2") && this->inputState.keys["up2"]) {
        // Move Up
        //this->position = this->position + upDir * moveAmount;
        this->position.z = this->position.z + 1.0f;
    }
    if (this->inputState.keys.count("down2") && this->inputState.keys["down2"]) {
        // Move Down
       // this->position = this->position + upDir * (-moveAmount);
        this->position.z = this->position.z - 1.0f;
    }
    if (this->inputState.keys.count("roll") && this->inputState.keys["roll"]) {
        // Move Down
       // this->position = this->position + upDir * (-moveAmount);
        roll = roll - 0.01f;
        updateCameraOrientation();
    }
    if (this->inputState.keys.count("roll2") && this->inputState.keys["roll2"]) {
        // Move Down
       // this->position = this->position + upDir * (-moveAmount);
        roll = roll + 0.01f;
        updateCameraOrientation();

    }

}



void ColoQuatCamera::updateDebug2(float deltaTime) {
    // Calculate the amount of movement for this frame.
    const float moveAmount = this->moveSpeed * deltaTime;

    // Calculate camera direction vectors from orientation by transforming
    // the world vectors with the camera's orientation quaternion.
    Vec3 forwardDir = transform(this->WORLD_FORWARD, this->orientation);
    Vec3 rightDir = transform(this->WORLD_RIGHT, this->orientation);
    Vec3 upDir = transform(this->WORLD_UP, this->orientation);

    // --- Handle Movement ---
    if (this->inputState.keys.count("forward2") && this->inputState.keys["forward2"]) {
        // Move Forward
        this->position.x = this->position.x + 0.1f;//this->position + forwardDir * moveAmount;
    }
    if (this->inputState.keys.count("backward2") && this->inputState.keys["backward2"]) {
        // Move Backward
        this->position.x = this->position.x - 0.1f;// this->position + forwardDir * (-moveAmount);
    }
    if (this->inputState.keys.count("left2") && this->inputState.keys["left2"]) {
        // Strafe Left
        this->position.y = this->position.y - 0.1f;// this->position + rightDir * (-moveAmount);
    }
    if (this->inputState.keys.count("right2") && this->inputState.keys["right2"]) {
        // Strafe Right
      //  this->position = this->position + rightDir * moveAmount;
        this->position.y = this->position.y + 0.1f;

    }

    if (this->inputState.keys.count("up2") && this->inputState.keys["up2"]) {
        // Move Up
        //this->position = this->position + upDir * moveAmount;
        this->position.z = this->position.z + 0.1f;
    }
    if (this->inputState.keys.count("down2") && this->inputState.keys["down2"]) {
        // Move Down
       // this->position = this->position + upDir * (-moveAmount);
        this->position.z = this->position.z - 0.1f;
    }

    if (this->inputState.keys.count("roll") && this->inputState.keys["roll"]) {
        // Move Down
       // this->position = this->position + upDir * (-moveAmount);
        roll = roll - 0.01f;
        updateCameraOrientation();
    }
    if (this->inputState.keys.count("roll2") && this->inputState.keys["roll2"]) {
        // Move Down
       // this->position = this->position + upDir * (-moveAmount);
        roll = roll + 0.01f;
        updateCameraOrientation();
    }

}



void  ColoQuatCamera::updateCameraOrientation() {
    // Clamp pitch to prevent flipping
  //  const maxPitch = Math.PI / 2 - 0.01 ; 
  // Z axis orientation but what if we remove clamp completely?


//	   const maxPitch = Math.PI / 2 - 0.01 + Math.PI;
    float  maxPitch = M_PI / 2 - 0.01 + M_PI;
    //   camera.pitch = Math.max(-maxPitch, Math.min(maxPitch, camera.pitch));
   //    pitch = Math.max(-maxPitch, Math.min(maxPitch, pitch));

   //	    pitch = std::max(-maxPitch, std::min(maxPitch, pitch)); // #include <algorithm> // For std::min and std::max


      // const yawQuat = quat.create();
    Quaternion yawQuat;

    // quat.setAxisAngle(yawQuat, WORLD_UP, camera.yaw); // Yaw around world Z
//quat.setAxisAngle(yawQuat, WORLD_UP, yaw); // Yaw around world Z
    yawQuat = Quaternion::fromAxisAngle(WORLD_UP, yaw);
    //  const pitchQuat = quat.create();
    Quaternion pitchQuat;
    //  quat.setAxisAngle(pitchQuat, WORLD_RIGHT, camera.pitch); // Pitch around world X
//quat.setAxisAngle(pitchQuat, WORLD_RIGHT, pitch); 
    pitchQuat = Quaternion::fromAxisAngle(WORLD_RIGHT, pitch); ;




    Quaternion rollQuat; // new
    rollQuat = Quaternion::fromAxisAngle(WORLD_FORWARD, roll); ; // new

    // Combine rotations: yaw first, then pitch in the new coordinate system
       //  quat.multiply(camera.orientation, yawQuat, pitchQuat);
     // orientation = yawQuat * pitchQuat; // old with no roll

     // Combine rotations: yaw first, then pitch, then roll.
     // The multiplication order is crucial for correct behavior.
     // Multiplying yawQuat * pitchQuat rotates the pitch axis along with the yaw.
     // Then, multiplying by rollQuat rotates the roll axis along with the
     // combined yaw-pitch orientation.

    // orientation = yawQuat * pitchQuat * rollQuat;// new,doesn't work?
         // orientation = rollQuat *yawQuat * pitchQuat ;// new
     // orientation = Quaternion::fromEulerAngles(yawQuat , pitchQuat , rollQuat);
    orientation = fromEulerAngles(yaw, pitch, roll);

    //https://stackoverflow.com/questions/5782658/extracting-yaw-from-a-quaternion
    //https://www.bartslinger.com/flight-dynamics/equations-of-motion-with-quaternions

  //  https://www.numberanalytics.com/blog/ultimate-guide-to-roll-pitch-yaw

     // quat.normalize(camera.orientation, camera.orientation);
   //  orientation = orientation.normalize();
    orientation.normalize();
}


/**
* @brief Sets up input callbacks with GLFW.
* This function should be called once after creating the GLFW window.
* @param window The GLFW window to listen on.
*/
/*
void ColoQuadCamera::setupInputListeners(GLFWwindow* window) {
    this->window = window;

    // Store a pointer to this instance in the window's user pointer.
    // This allows the static callbacks to access the camera object.
    glfwSetWindowUserPointer(window, this);

    // Set the static callback functions for keyboard and mouse.
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);

    // Disable the cursor and capture it for a better mouse-look experience.
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}*/

/**
 * @brief Static callback for keyboard input.
 * @param window The GLFW window that received the event.
 * @param key The key that was pressed or released.
 * @param scancode The system-specific scancode of the key.
 * @param action The action, GLFW_PRESS, GLFW_RELEASE, or GLFW_REPEAT.
 * @param mods Bit field describing which modifier keys were held down.
 */

 // save for reportable override - call in different call for differiataial equations
 /*

void ColoQuatCamera::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Retrieve the camera instance from the window user pointer.
    ColoQuadCamera* camera = this;//static_cast<ColoQuadCamera*>(glfwGetWindowUserPointer(window));
    if (!camera) return;

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_W) camera->inputState.keys["forward"] = true;
        if (key == GLFW_KEY_S) camera->inputState.keys["backward"] = true;
        if (key == GLFW_KEY_A) camera->inputState.keys["left"] = true;
        if (key == GLFW_KEY_D) camera->inputState.keys["right"] = true;
        if (key == GLFW_KEY_SPACE) camera->inputState.keys["up"] = true;
        if (key == GLFW_KEY_LEFT_SHIFT) camera->inputState.keys["down"] = true;
    } else if (action == GLFW_RELEASE) {
        if (key == GLFW_KEY_W) camera->inputState.keys["forward"] = false;
        if (key == GLFW_KEY_S) camera->inputState.keys["backward"] = false;
        if (key == GLFW_KEY_A) camera->inputState.keys["left"] = false;
        if (key == GLFW_KEY_D) camera->inputState.keys["right"] = false;
        if (key == GLFW_KEY_SPACE) camera->inputState.keys["up"] = false;
        if (key == GLFW_KEY_LEFT_SHIFT) camera->inputState.keys["down"] = false;
    }
}
*/

void ColoQuatCamera::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Retrieve the camera instance from the window user pointer.
   // ColoQuadCamera* camera = this;//static_cast<ColoQuadCamera*>(glfwGetWindowUserPointer(window));
   // if (!camera) return;

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_W) inputState.keys["forward"] = true;
        if (key == GLFW_KEY_S) inputState.keys["backward"] = true;
        if (key == GLFW_KEY_A) inputState.keys["left"] = true;
        if (key == GLFW_KEY_D) inputState.keys["right"] = true;
        if (key == GLFW_KEY_SPACE) inputState.keys["up"] = true;
        if (key == GLFW_KEY_LEFT_SHIFT) inputState.keys["down"] = true;
    }
    else if (action == GLFW_RELEASE) {
        if (key == GLFW_KEY_W) inputState.keys["forward"] = false;
        if (key == GLFW_KEY_S) inputState.keys["backward"] = false;
        if (key == GLFW_KEY_A) inputState.keys["left"] = false;
        if (key == GLFW_KEY_D) inputState.keys["right"] = false;
        if (key == GLFW_KEY_SPACE) inputState.keys["up"] = false;
        if (key == GLFW_KEY_LEFT_SHIFT) inputState.keys["down"] = false;
    }
}


void ColoQuatCamera::keyCallbackDebug(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Retrieve the camera instance from the window user pointer.
   // ColoQuadCamera* camera = this;//static_cast<ColoQuadCamera*>(glfwGetWindowUserPointer(window));
   // if (!camera) return;

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_T) inputState.keys["forward2"] = true;
        if (key == GLFW_KEY_G) inputState.keys["backward2"] = true;
        if (key == GLFW_KEY_F) inputState.keys["left2"] = true;
        if (key == GLFW_KEY_H) inputState.keys["right2"] = true;
        if (key == GLFW_KEY_R) inputState.keys["up2"] = true;
        if (key == GLFW_KEY_Y) inputState.keys["down2"] = true;
        if (key == GLFW_KEY_I) inputState.keys["roll"] = true;
        if (key == GLFW_KEY_O) inputState.keys["roll2"] = true;
    }
    else if (action == GLFW_RELEASE) {
        if (key == GLFW_KEY_T) inputState.keys["forward2"] = false;
        if (key == GLFW_KEY_G) inputState.keys["backward2"] = false;
        if (key == GLFW_KEY_F) inputState.keys["left2"] = false;
        if (key == GLFW_KEY_H) inputState.keys["right2"] = false;
        if (key == GLFW_KEY_R) inputState.keys["up2"] = false;
        if (key == GLFW_KEY_Y) inputState.keys["down2"] = false;
        if (key == GLFW_KEY_I) inputState.keys["roll"] = false;
        if (key == GLFW_KEY_O) inputState.keys["roll2"] = false;
    }
}

/**
 * @brief Static callback for mouse movement.
 * @param window The GLFW window that received the event.
 * @param xpos The new x-coordinate of the cursor.
 * @param ypos The new y-coordinate of the cursor.
 */
 // save for reportable override - call in different call for differiataial equations
 /*
void ColoQuadCamera::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    // Retrieve the camera instance from the window user pointer.
    ColoQuadCamera* camera = this; // static_cast<ColoQuadCamera*>(glfwGetWindowUserPointer(window));
    if (!camera) return;

    // Handle initial mouse position on first call
    if (camera->inputState.mouse.lastX == 0.0f && camera->inputState.mouse.lastY == 0.0f) {
        camera->inputState.mouse.lastX = xpos;
        camera->inputState.mouse.lastY = ypos;
    }

    float dx = xpos - camera->inputState.mouse.lastX;
    float dy = ypos - camera->inputState.mouse.lastY;

    // Update yaw and pitch
    camera->yaw -= dx * camera->rotateSpeed;
    camera->pitch -= dy * camera->rotateSpeed;

    // Recalculate camera orientation with new angles
    camera->updateCameraOrientation();

    // Update last mouse position
    camera->inputState.mouse.lastX = xpos;
    camera->inputState.mouse.lastY = ypos;
}

*/


void ColoQuatCamera::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    // Retrieve the camera instance from the window user pointer.
  //  ColoQuadCamera* camera = this; // static_cast<ColoQuadCamera*>(glfwGetWindowUserPointer(window));
  //  if (!camera) return;

    // Handle initial mouse position on first call
    if (inputState.mouse.lastX == 0.0f && inputState.mouse.lastY == 0.0f) {
        inputState.mouse.lastX = xpos;
        inputState.mouse.lastY = ypos;
    }

    float dx = xpos - inputState.mouse.lastX;
    float dy = ypos - inputState.mouse.lastY;

    // Update yaw and pitch
    yaw -= dx * rotateSpeed;
    pitch -= dy * rotateSpeed;

    // Recalculate camera orientation with new angles
    updateCameraOrientation();

    // Update last mouse position
    inputState.mouse.lastX = xpos;
    inputState.mouse.lastY = ypos;
}

// Note: This file needs to be part of the same project as quat-camera.h
// and should have access to the gosha_math2.h library and its functions.

/**
 * @brief Updates the camera's perspective and view matrices.
 * This function should be called once per frame, after the camera's position
 * and orientation have been updated. It populates the member variables
 * `perpective` and `view`.
 */
void ColoQuatCamera::updateCameraMatrixes()
{
    // --- 1. Calculate the Perspective Matrix ---
    const float fieldOfView = 45.0f * M_PI / 180.0f; // Convert degrees to radians
    float aspect = 1.0f; // Default to 1.0 to prevent division by zero
    if (m_iHeight > 0) {
        aspect = static_cast<float>(m_iWidth) / static_cast<float>(m_iHeight);
    }
    const float zNear = 0.1f;
    const float zFar = 1000.0f; // Increased zFar for a larger view distance

    // Use the gosha_math library's perspective function.
    // This is equivalent to gl-matrix's `mat4.perspective`.
 //   perpective = Mat4::perspective(fieldOfView, aspect, zNear, zFar);
  //  camera_projection = glm::perspective(glm::radians(camera_fov), (float)m_screen_width / (float)m_screen_height, 0.1f, 100.0f);
    perpective = Mat4::perspective(glm::degrees(fieldOfView), aspect, zNear, zFar);

    // --- 2. Calculate the View Matrix ---
    // The view matrix is the inverse of the camera's world transformation.
    // In quaternion math, the inverse of a rotation quaternion is its conjugate.
    // For unit quaternions, this is simply negating the x, y, z components.
    Quaternion invOrientation = this->orientation;
    invOrientation.x = -invOrientation.x;
    invOrientation.y = -invOrientation.y;
    invOrientation.z = -invOrientation.z;

    // Create a rotation matrix from the inverse orientation quaternion.
    // gosha_math::fromQuat is assumed to exist and return a 4x4 rotation matrix.
    //Mat4 invRotationMatrix = gosha_math::fromQuat(invOrientation);
    Mat4 invRotationMatrix = fromQuat(invOrientation);

    // Create a translation matrix for the inverse of the camera's position.
    // The view matrix moves the entire world opposite to the camera's movement.
  //  Mat4 translationMatrix = translate(Mat4::Identity(), -this->position);
 //   Mat4 translationMatrix = translate(Mat4::Identity(), -position);
    Mat4 translationMatrix = Mat4::Identity().translate(-position);

    // Combine the inverse rotation and inverse translation.
    // The order is important: View = Inv(Rotation) * Inv(Translation)
    view = invRotationMatrix * translationMatrix;//Mat4::multiply(invRotationMatrix, translationMatrix);
}



/**
 * @brief Recodes the camera to look at a 2D rectangle.
 * The camera will be positioned to view the entire rectangle defined by (0,0) and (1024,768).
 * This function modifies the camera's position, pitch, yaw, and perspective matrix to achieve
 * an orthographic-like view of the specified 2D area.
 *
 * @param x The x-coordinate of the top-left corner of the 2D rectangle.
 * @param y The y-coordinate of the top-left corner of the 2D rectangle.
 * @param width The width of the 2D rectangle.
 * @param height The height of the 2D rectangle.
 */

void ColoQuatCamera::lookAt2DRect(float x, float y, float width, float height)
{
    // 1. Set up the orthographic projection matrix.
    // An orthographic projection matrix is typically used for 2D rendering.
    // It maps a 3D box (left, right, bottom, top, near, far) to the screen.
    // Since we are viewing a 2D rect, we can simplify this.
    perpective = Mat4::ortho(x, x + width, y + height, y, -100.0f, 100.0f);
    // Note: The y-axis in screen space is often inverted, so (y + height, y) is used.
    // The Z-near and Z-far values are chosen to be large enough to encompass
    // all the geometry you'll be drawing in this 2D view.

    // 2. Set up the view matrix.
    // For a 2D view, we want a simple translation and no rotation.
    // The view matrix moves the world, so we need to translate the world
    // by the negative of the camera's position.

    // Since we're in 2D, we can simplify the camera's position.
    // We want the camera to be "looking straight down" (if Z is up)
    // or "looking straight in" (if Z is depth). Let's assume Z is depth
    // for a 2D view.

    // A good default position is at the center of the rectangle,
    // with a Z value that ensures everything is in view.
    float centerX = x + width / 2.0f;
    float centerY = y + height / 2.0f;

    // We can reset the camera's rotation to identity for a simple 2D view.
    orientation = Quaternion(); // Identity quaternion
    pitch = 0.0f;
    yaw = 0.0f;

    // Position the camera
    position = Vec3(centerX, centerY, 0.0f); // Position camera at center of view, on z=0 plane.

    // The view matrix is the inverse of the camera's transform.
    // Since we have an identity rotation, the view matrix is just a translation.
    //Mat4 view2;
    view = Mat4::Identity().translate(-position);;//view2.translate(Mat4::Identity(), -position);
    // Mat4::Identity().translate( -position);

     // Recalculate camera orientation (though it's identity, this is good practice)
    updateCameraOrientation();

}

/*
void ColoQuatCamera::lookAt2DRect2(float x, float y, float width, float height)
{
    // 1. Set up the orthographic projection matrix.
    // An orthographic projection matrix is typically used for 2D rendering.
    // It maps a 3D box (left, right, bottom, top, near, far) to the screen.
    // Since we are viewing a 2D rect, we can simplify this.
 //   perpective = Mat4::ortho(x, x + width, y + height, y, -100.0f, 100.0f);
    // Note: The y-axis in screen space is often inverted, so (y + height, y) is used.
    // The Z-near and Z-far values are chosen to be large enough to encompass
    // all the geometry you'll be drawing in this 2D view.

    // 2. Set up the view matrix.
    // For a 2D view, we want a simple translation and no rotation.
    // The view matrix moves the world, so we need to translate the world
    // by the negative of the camera's position.

    // Since we're in 2D, we can simplify the camera's position.
    // We want the camera to be "looking straight down" (if Z is up)
    // or "looking straight in" (if Z is depth). Let's assume Z is depth
    // for a 2D view.

    // A good default position is at the center of the rectangle,
    // with a Z value that ensures everything is in view.

     // --- 1. Calculate the Perspective Matrix ---
    const float fieldOfView = 45.0f * M_PI / 180.0f; // Convert degrees to radians
    float aspect = 1.0f; // Default to 1.0 to prevent division by zero
    if (m_iHeight > 0) {
        aspect = static_cast<float>(m_iWidth) / static_cast<float>(m_iHeight);
    }
    const float zNear = 0.1f;
    const float zFar = 1000.0f; // Increased zFar for a larger view distance

    // Use the gosha_math library's perspective function.
    // This is equivalent to gl-matrix's `mat4.perspective`.
    perpective = Mat4::perspective(fieldOfView, aspect, zNear, zFar);


    float centerX = x + width / 2.0f;
    float centerY = y + height / 2.0f;

    // We can reset the camera's rotation to identity for a simple 2D view.
    orientation = Quaternion(); // Identity quaternion
    pitch = 0.0f;
    yaw = 0.0f;

    // Position the camera
    position = Vec3(centerX, centerY, 0.0f); // Position camera at center of view, on z=0 plane.

    // The view matrix is the inverse of the camera's transform.
    // Since we have an identity rotation, the view matrix is just a translation.
    //Mat4 view2;
    view = Mat4::Identity().translate( -position);;//view2.translate(Mat4::Identity(), -position);
   // Mat4::Identity().translate( -position);

    // Recalculate camera orientation (though it's identity, this is good practice)
    updateCameraOrientation();

}
*/
/*
void ColoQuatCamera::lookAt2DRect2(float x, float y, float width, float height)
{
    // --- 1. Set up the perspective projection matrix to match the 2D view ---

    // First, determine the Z distance of the camera from the plane.
    // A good value is one that is large enough to minimize perspective distortion,
    // but not so large that it causes floating-point precision issues with zNear and zFar.
    // We can also make it a multiple of the height to keep things relative.
    const float distance = height;

    // The perspective frustum's height at a given distance is determined by the FoV.
    // We can use trigonometry to calculate the required vertical FoV to perfectly
    // frame the given height at our chosen distance.
    const float halfHeight = height / 2.0f;
    const float verticalFieldOfView = 2.0f * atanf(halfHeight / distance); // Result is in radians

    // Calculate the aspect ratio from the provided width and height.
    // This is crucial for the perspective matrix to scale correctly.
    float aspect = 1.0f;
    if (height > 0) {
        aspect = width / height;
    }

    // Set zNear to a small value and zFar to a large one to capture all geometry.
    // zNear must be less than 'distance' so the rectangle is visible.
    const float zNear = 0.1f;
    const float zFar = 1000.0f;

    // Use the gosha_math library's perspective function with the calculated values.
    perpective = Mat4::perspective(verticalFieldOfView, aspect, zNear, zFar);

    // --- 2. Set up the view matrix ---

    // For the view matrix, we want to position the camera at the center of the rectangle
    // but at the specified 'distance' along the Z-axis.
    float centerX = x; //- width / 2.0f;
    float centerY = y ;//+ height / 2.0f;

    // Set the camera's position to look at the center of the rectangle.
    // The Z position is negative because we are looking down the negative Z-axis in a
    // typical right-handed coordinate system (OpenGL/DirectX convention).
  //  position = Vec3(centerX, centerY, distance);

    // For a 2D view, we want the camera to look straight ahead.
    // Resetting the rotation to identity and calculating the view matrix.
  //  orientation = Quaternion(); // Identity quaternion
  //  pitch = 0.0f;
  //  yaw = 0.0f;


    // The view matrix is the inverse of the camera's transform.
    // It's a rotation and a translation. Since our rotation is identity,
    // it's just a translation by the negative of the position.
  //  view = Mat4::Identity().translate(-position);

 // --- 2. Set up the view matrix using a lookAt function ---

    // Define the camera's position.
    // It should be at the center of the rectangle's x and y, and at 'distance' on the z-axis.
    // We use a positive Z because typical 3D libraries (like OpenGL) use a right-handed
    // coordinate system where the camera looks down the negative Z-axis. So, to see
    // the xy-plane at z=0, the camera needs to be at a positive Z value.
    const Vec3 cameraPosition = Vec3(x, y, distance);

    // Define the target the camera is looking at.
    // We want to look at the center of the rectangle, which is on the z=0 plane.
    const Vec3 target = Vec3(x, y, 0.0f);

    // Define the "up" vector. For a 2D view, we want the camera's up to be the world's up.
    // This is typically the positive Y-axis.
    const Vec3 upVector = Vec3(0.0f, 1.0f, 0.0f);

    // Use a Mat4::lookAt function to calculate the view matrix.
    // This function handles the necessary translation and rotation for the camera.
    view = Mat4::lookAt(cameraPosition, target, upVector);

    // The following lines are not needed if using Mat4::lookAt, as the orientation
    // and position are now encapsulated in the view matrix. However, if you need to
    // keep the camera's state variables updated for other parts of the application,
    // you can set them here.
    position = cameraPosition;

    // Recalculate camera orientation (good practice)
  //  updateCameraOrientation();
}
*/

/*
void ColoQuatCamera::lookAt2DRect2(float x, float y, float width, float height)
{
     // --- 1. Calculate the Perspective Matrix ---
    const float fieldOfView = 45.0f * M_PI / 180.0f; // Convert degrees to radians
    float aspect = 1.0f; // Default to 1.0 to prevent division by zero
    if (m_iHeight > 0) {
        aspect = static_cast<float>(m_iWidth) / static_cast<float>(m_iHeight);
    }
    const float zNear = 0.1f;
    const float zFar = 1000.0f; // Increased zFar for a larger view distance

    // Use the gosha_math library's perspective function.
    // This is equivalent to gl-matrix's `mat4.perspective`.
    perpective = Mat4::perspective(fieldOfView, aspect, zNear, zFar);
    // 1. Set up the orthographic projection matrix.
    // An orthographic projection matrix is typically used for 2D rendering.
    // It maps a 3D box (left, right, bottom, top, near, far) to the screen.
    // Since we are viewing a 2D rect, we can simplify this.
  //  perpective = Mat4::ortho(x, x + width, y + height, y, -100.0f, 100.0f);


    // Note: The y-axis in screen space is often inverted, so (y + height, y) is used.
    // The Z-near and Z-far values are chosen to be large enough to encompass
    // all the geometry you'll be drawing in this 2D view.

    // 2. Set up the view matrix.
    // For a 2D view, we want a simple translation and no rotation.
    // The view matrix moves the world, so we need to translate the world
    // by the negative of the camera's position.

    // Since we're in 2D, we can simplify the camera's position.
    // We want the camera to be "looking straight down" (if Z is up)
    // or "looking straight in" (if Z is depth). Let's assume Z is depth
    // for a 2D view.

    // A good default position is at the center of the rectangle,
    // with a Z value that ensures everything is in view.
 //   float centerX = x ;//+ width / 2.0f;
 //   float centerY = y + height / 2.0f;
 //   centerY =0 ;

    // We can reset the camera's rotation to identity for a simple 2D view.
  //  orientation = Quaternion(); // Identity quaternion
  //  pitch = 0.0f;
  //  yaw = 0.0f;

    // Position the camera
   // position = Vec3(centerX, centerY, 0.0f); // Position camera at center of view, on z=0 plane.

    // The view matrix is the inverse of the camera's transform.
    // Since we have an identity rotation, the view matrix is just a translation.
    //Mat4 view2;
  //  view = Mat4::Identity().translate( -position);;//view2.translate(Mat4::Identity(), -position);
   // Mat4::Identity().translate( -position);

    // Recalculate camera orientation (though it's identity, this is good practice)
    //updateCameraOrientation();

    const Vec3 upVector = Vec3(0.0f, 1.0f, 0.0f);

    position = Vec3(x+100.0f, y + 40.0f, -10.0f );

      view = Mat4::lookAt(position, position + WORLD_UP, upVector);


}
*/
//#include "quat_camera.h"

// Note: This assumes you have the necessary headers and a library that provides
// Vec3, Quaternion, and Mat4 classes with the required operators and functions.
#include <algorithm> // For std::min and std::max
#include <GLFW/glfw3.h>
#include <cmath> // For M_PI


// Existing member function from your previous code...
// ColoQuatCamera::ColoQuatCamera(...)
// ColoQuatCamera::~ColoQuatCamera()
// ...
// ...

/**
 * @brief Sets the camera's view to look at an XY plane with 3D projection.
 * The camera will be positioned to view the center of the specified rectangle (x,y)
 * with the given width and height. It will use a perspective projection.
 *
 * @param x The x-coordinate of the center of the 2D plane to look at.
 * @param y The y-coordinate of the center of the 2D plane to look at.
 * @param width The width of the 2D plane.
 * @param height The height of the 2D plane.
 */
void ColoQuatCamera::lookAt2DRect2(float x, float y, float width, float height)
{
    // --- 1. Calculate the Perspective Matrix ---
    // This part remains the same as your original perspective projection,
    // as we want to maintain a 3D feel.
    const float fieldOfView = 45.0f * M_PI / 180.0f; // Convert degrees to radians
    float aspect = 1.0f; // Default to 1.0 to prevent division by zero
    if (m_iHeight > 0) {
        aspect = static_cast<float>(m_iWidth) / static_cast<float>(m_iHeight);
    }
    const float zNear = 0.1f;
    const float zFar = 1000.0f; // Increased zFar for a larger view distance

    perpective = Mat4::perspective(fieldOfView, aspect, zNear, zFar);

    // --- 2. Set up the View Matrix ---
    // The goal is to position the camera so it is "looking at" the specified
    // 2D rectangle, which lies on the XY plane.

    // Calculate the camera's position.
    // We want the camera to be at a certain distance from the center of the rectangle.
    // The 'distance' determines how zoomed in or out the view is.
    // We can calculate a suitable distance based on the FOV and the dimensions
    // of the rectangle to ensure it fits in the view.

    // Let's position the camera at a distance from the center,
    // along the positive Z-axis (assuming Z is depth here).

    // Calculate the distance to see the whole width.
    // tan(fov_x / 2) = (width/2) / distance_x
    // distance_x = (width/2) / tan(fov_x / 2)
    // fov_x = fov_y * aspect
    float fovX = fieldOfView * aspect;
    float distToSeeWidth = (width / 2.0f) / tan(fovX / 2.0f);

    // Calculate the distance to see the whole height.
    // tan(fov_y / 2) = (height/2) / distance_y
    // distance_y = (height/2) / tan(fov_y / 2)
    float distToSeeHeight = (height / 2.0f) / tan(fieldOfView / 2.0f);

    // Use the larger of the two distances to ensure the entire rectangle is visible.
    float distance = std::max(distToSeeWidth, distToSeeHeight);

    // The camera's position should be at the center of the rectangle,
    // but moved back along the Z-axis by the calculated distance.
    // Let's assume the XY plane is at z=0.
    position = Vec3(x, y, distance);

    // The point the camera is looking at is the center of the rectangle on the XY plane.
    Vec3 target = Vec3(x, y, 0.0f);

    // The "up" vector is typically Vec3(0, 1, 0) for a standard camera,
    // but since we're looking at the XY plane, our "up" is Vec3(0,0,1).
    // Let's use Vec3(0.0f, 1.0f, 0.0f) for a typical 3D lookAt setup.
    // If your "up" is Z, you should use WORLD_UP. Let's assume WORLD_UP is Z.
    const Vec3 upVector = WORLD_UP; // Or Vec3(0.0f, 1.0f, 0.0f) depending on your coordinate system.

    // Use the lookAt function to create the view matrix.
    // Mat4::lookAt(camera_position, target_position, up_vector)
    view = Mat4::lookAt(position, target, upVector);

    // Update the camera's orientation based on the new view matrix.
    // This is a bit tricky, but we can extract the orientation from the view matrix.
    // The view matrix is the inverse of the camera's world matrix.
    // We can get the camera's world matrix by inverting the view matrix.
    // The rotation part of the world matrix is the camera's orientation.
    Mat4 cameraWorldMatrix = view.inverse();
    orientation = fromMat4(cameraWorldMatrix);
    // You might need a helper function like `Quaternion::fromMat4(Mat4)`
    // to perform this conversion.

    // If you don't have a `fromMat4` function, you can directly calculate
    // yaw and pitch from the lookAt vectors and update the orientation manually.
    // This is more complex and less robust. The quaternion approach is better.

    // The yaw and pitch member variables can be updated from the orientation,
    // but this is often not necessary if you are not using them for
    // subsequent rotation calculations (e.g., in mouse callback).
}


// --- Recoded functions to convert Mat4 to glm::mat4 ---

glm::mat4 ColoQuatCamera::GetGLMProjectionMatrix() {
    glm::mat4 glm_projection; // Initialize a default glm::mat4

    // Copy elements from the Mat4 to the glm::mat4
    // GLM's access is mat[col][row], which matches your Mat4's layout
    for (int col = 0; col < 4; ++col) {
        for (int row = 0; row < 4; ++row) {
            //   glm_projection[col][row] = perspective.m[col][row];
            glm_projection[col][row] = perpective.m[col][row];

        }
    }
    return glm_projection;
}

glm::mat4 ColoQuatCamera::GetGLMViewMatrix() {
    glm::mat4 glm_view; // Initialize a default glm::mat4

    // Copy elements from the Mat4 to the glm::mat4
    for (int col = 0; col < 4; ++col) {
        for (int row = 0; row < 4; ++row) {
            glm_view[col][row] = view.m[col][row];
        }
    }
    return glm_view;
}


ColoQuatCamera* g_ColoQuatCamera;

/*
void ColoQuadCamera::updateCameraMatrixes()
{
    const fieldOfView = 45 * Math.PI / 180;
        const aspect = gl.canvas.clientWidth / gl.canvas.clientHeight;
        const zNear = 0.1;
        const zFar = 100.0;
        const projectionMatrix = mat4.create();
        mat4.perspective(projectionMatrix, fieldOfView, aspect, zNear, zFar);

        // Create view matrix from camera position and orientation
        const viewMatrix = mat4.create();
        const rotationMatrix = mat4.fromQuat(mat4.create(), camera.orientation);
        const invCameraPos = vec3.scale(vec3.create(), camera.position, -1);
        const translationMatrix = mat4.translate(mat4.create(), mat4.create(), invCameraPos);

        // View = Inverse(Translate * Rotate) = Inverse(Rotate) * Inverse(Translate)
        // Inverse of rotation matrix is its transpose. fromQuat already gives an orthonormal matrix.
        // But it's easier to think of it as moving the world, not the camera.
        // So: first rotate the world by the inverse camera rotation, then translate it.
        const invOrientation = quat.create();
        invOrientation[0] = -camera.orientation[0];
        invOrientation[1] = -camera.orientation[1];
        invOrientation[2] = -camera.orientation[2];
        invOrientation[3] = camera.orientation[3];

        const invRotationMatrix = mat4.fromQuat(mat4.create(), invOrientation);
        mat4.multiply(viewMatrix, invRotationMatrix, translationMatrix);

        // --- Draw Grid Floor ---
        const modelViewMatrix = mat4.create(); // Identity matrix for grid, already at origin.
        mat4.multiply(modelViewMatrix, viewMatrix, modelViewMatrix); // Apply camera


}*/