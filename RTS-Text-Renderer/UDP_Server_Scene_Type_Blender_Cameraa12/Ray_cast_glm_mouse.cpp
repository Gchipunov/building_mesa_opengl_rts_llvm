
#include "Ray_cast_glm_mouse.h"

// https://education.siggraph.org/static/HyperGraph/raytrace/rtinter3.htm
// https://education.siggraph.org/static/HyperGraph/raytrace/rtinter0.htm
// https://education.siggraph.org/static/HyperGraph/raytrace/rayplane_intersection.htm
// https://education.siggraph.org/static/HyperGraph/toc.htm

// http://fileadmin.cs.lth.se/cs/Personal/Tomas_Akenine-Moller/raytri
// 
// 
/**
 * @brief Prints a glm::mat4 matrix to the console.
 *
 * @param matrix The glm::mat4 to print.
 */
void print_cout_glm_mat4(const glm::mat4& matrix) {
    // Set up formatting for consistent width and precision
    //std::cout << std::fixed << std::setprecision(4);

    // Print the matrix in a human-readable row-by-row format
    std::cout << "glm::mat4:\n";
    for (int row = 0; row < 4; ++row) {
        std::cout << "| ";
        for (int col = 0; col < 4; ++col) {
            // Access element using [col][row] as per GLM's convention
            std::cout << matrix[col][row] << " ";
        }
        std::cout << "|" << std::endl;;
    }
}

/**
 * @brief Prints a glm::mat4 matrix to the console using printf.
 *
 * @param matrix The glm::mat4 to print.
 */
void print_printf_glm_mat4_printf(const glm::mat4& matrix) {
    printf("glm::mat4:\n");
    for (int row = 0; row < 4; ++row) {
        printf("| ");
        for (int col = 0; col < 4; ++col) {
            // Access element using [col][row] and format with printf
            printf("%8.4f ", matrix[col][row]);
        }
        printf("|\n");
    }
}
// checkMouseClick(create_ray_from_mouse
Ray create_ray_from_mouse(
    int mouse_x, int mouse_y, int screen_width, int screen_height,
    const glm::mat4& view_matrix, const glm::mat4& projection_matrix) {

    Ray ray;
    //    printf("create_ray_from_mouse: %d %d\n", mouse_x, mouse_y);

     //   printf("viewmatrix:\n");
     //   print_printf_glm_mat4_printf(view_matrix);
     //   printf("\n");
    //    printf("projection_matrix:\n");
     //   print_printf_glm_mat4_printf(projection_matrix);
     //   printf("\n");

        // 1. Convert screen coordinates to Normalized Device Coordinates (NDC)
        // The screen coordinates (0,0 at top-left) are converted to NDC (-1 to 1 for x, -1 to 1 for y).
        // The Z value of 0.0 projects onto the near plane, and 1.0 projects onto the far plane.
    glm::vec3 screen_coords_near = glm::vec3(
        (float)mouse_x,
        (float)(screen_height - mouse_y), // Flip y-coordinate to match OpenGL's bottom-left origin
        0.0f
    );

    glm::vec3 screen_coords_far = glm::vec3(
        (float)mouse_x,
        (float)(screen_height - mouse_y), // Flip y-coordinate to match OpenGL's bottom-left origin
        1.0f
    );

    // 2. Unproject the points from screen space to world space
    // glm::unProject takes screen coordinates and the combined model-view-projection matrix
    // to transform them back into world space.
    glm::mat4 inv_view_proj_matrix = glm::inverse(projection_matrix * view_matrix);

    // Unproject the near plane point to get the ray's origin
    glm::vec4 world_near_pos = inv_view_proj_matrix * glm::vec4(
        (2.0f * mouse_x) / screen_width - 1.0f,
        1.0f - (2.0f * mouse_y) / screen_height,
        -1.0f, // Use -1.0 for z to get the near plane position
        1.0f
    );
    ray.origin = glm::vec3(world_near_pos) / world_near_pos.w;

    // Unproject the far plane point to get a point for the direction
    glm::vec4 world_far_pos = inv_view_proj_matrix * glm::vec4(
        (2.0f * mouse_x) / screen_width - 1.0f,
        1.0f - (2.0f * mouse_y) / screen_height,
        1.0f, // Use 1.0 for z to get the far plane position
        1.0f
    );
    glm::vec3 world_far_point = glm::vec3(world_far_pos) / world_far_pos.w;

    // 3. The ray direction is the vector from the near point to the far point
    ray.direction = glm::normalize(world_far_point - ray.origin);

    return ray;
}


Ray create_ray_from_mouse_normalized(
    float virtual_mouse_x, int virtual_mouse_y, int screen_width, int screen_height,
    const glm::mat4& view_matrix, const glm::mat4& projection_matrix) {

    Ray ray;
    //   printf("create_ray_from_mouse_normalized_virtualized: %f %f\n", virtual_mouse_x, virtual_mouse_y);

     //  printf("viewmatrix:\n");
     //  print_printf_glm_mat4_printf(view_matrix);
     //  printf("\n");
     //  printf("projection_matrix:\n");
    //   print_printf_glm_mat4_printf(projection_matrix);
     //  printf("\n");

       // 1. Convert screen coordinates to Normalized Device Coordinates (NDC)
       // The screen coordinates (0,0 at top-left) are converted to NDC (-1 to 1 for x, -1 to 1 for y).
       // The Z value of 0.0 projects onto the near plane, and 1.0 projects onto the far plane.
      /*
       glm::vec3 screen_coords_near = glm::vec3(
           (float)mouse_x,
           (float)(screen_height - mouse_y), // Flip y-coordinate to match OpenGL's bottom-left origin
           0.0f
       );

       glm::vec3 screen_coords_far = glm::vec3(
           (float)mouse_x,
           (float)(screen_height - mouse_y), // Flip y-coordinate to match OpenGL's bottom-left origin
           1.0f
       );*/

       // 2. Unproject the points from screen space to world space
       // glm::unProject takes screen coordinates and the combined model-view-projection matrix
       // to transform them back into world space.
    glm::mat4 inv_view_proj_matrix = glm::inverse(projection_matrix * view_matrix);

    // Unproject the near plane point to get the ray's origin
    glm::vec4 world_near_pos = inv_view_proj_matrix * glm::vec4(
        virtual_mouse_x,
        (1.0f - virtual_mouse_y) - 0.5f,
        -1.0f, // Use -1.0 for z to get the near plane position
        1.0f
    );
    ray.origin = glm::vec3(world_near_pos) / world_near_pos.w;

    // Unproject the far plane point to get a point for the direction
    glm::vec4 world_far_pos = inv_view_proj_matrix * glm::vec4(
        virtual_mouse_x,
        //virtual_mouse_y,
        (1.0f - virtual_mouse_y) - 0.5f,
        1.0f, // Use 1.0 for z to get the far plane position
        1.0f
    );
    glm::vec3 world_far_point = glm::vec3(world_far_pos) / world_far_pos.w;

    // 3. The ray direction is the vector from the near point to the far point
    ray.direction = glm::normalize(world_far_point - ray.origin);

    return ray;
}

Ray create_ray_from_mouse_unproject(
    int mouse_x, int mouse_y, int screen_width, int screen_height,
    const glm::mat4& view_matrix, const glm::mat4& projection_matrix) {

    Ray ray;

    // 1. Define the viewport (screen dimensions)
    glm::vec4 viewport = glm::vec4(0, 0, screen_width, screen_height);

    // 2. Unproject the near plane point
    glm::vec3 world_near_pos = glm::unProject(
        glm::vec3(mouse_x, screen_height - mouse_y, 0.0f), // Flip Y here
        view_matrix,
        projection_matrix,
        viewport
    );

    // 3. Unproject the far plane point
    glm::vec3 world_far_pos = glm::unProject(
        glm::vec3(mouse_x, screen_height - mouse_y, 1.0f), // Flip Y here
        view_matrix,
        projection_matrix,
        viewport
    );

    // 4. Set the ray origin and direction
    ray.origin = world_near_pos;
    ray.direction = glm::normalize(world_far_pos - world_near_pos);

    return ray;
}


/**
 * @brief Creates a ray from 2D mouse coordinates in screen space.
 * This function uses glm::unProject to efficiently convert screen coordinates
 * into a ray in world space.
 *
 * @param mouse_x The x-coordinate of the mouse in screen space (e.g., pixels).
 * @param mouse_y The y-coordinate of the mouse in screen space (e.g., pixels).
 * @param screen_width The width of the viewport.
 * @param screen_height The height of the viewport.
 * @param view_matrix The camera's view matrix.
 * @param projection_matrix The projection matrix (perspective or orthographic).
 * @return A Ray structure containing the origin and normalized direction.
 */
 /*
Ray create_ray_from_mouse(
    int mouse_x, int mouse_y, int screen_width, int screen_height,
    const glm::mat4& view_matrix, const glm::mat4& projection_matrix) {

    Ray ray;

    // The screen coordinates (0,0 at top-left) are converted to NDC (-1 to 1).
    // The Z value of -1.0 projects onto the near plane, and 1.0 onto the far plane.
    glm::mat4 inv_view_proj_matrix = glm::inverse(projection_matrix * view_matrix);

    // Unproject the near plane point to get the ray's origin
    glm::vec4 world_near_pos = inv_view_proj_matrix * glm::vec4(
        (2.0f * mouse_x) / screen_width - 1.0f,
        1.0f - (2.0f * mouse_y) / screen_height,
        -1.0f, // Use -1.0 for z to get the near plane position
        1.0f
    );
    ray.origin = glm::vec3(world_near_pos) / world_near_pos.w;

    // Unproject the far plane point to get a point for the direction
    glm::vec4 world_far_pos = inv_view_proj_matrix * glm::vec4(
        (2.0f * mouse_x) / screen_width - 1.0f,
        1.0f - (2.0f * mouse_y) / screen_height,
        1.0f, // Use 1.0 for z to get the far plane position
        1.0f
    );
    glm::vec3 world_far_point = glm::vec3(world_far_pos) / world_far_pos.w;

    // The ray direction is the normalized vector from the near point to the far point
    ray.direction = glm::normalize(world_far_point - ray.origin);

    return ray;
}
*/

glm::vec2 checkMouseClick(Ray my_ray,
    glm::vec3 v0,//(-1.0f, -1.0f, 0.0f),
    glm::vec3 v1,//(1.0f, -1.0f, 0.0f),
    glm::vec3 v2//(0.0f, 1.0f, 0.0f)
)
{

    // --- Step 5: Perform the intersection test ---
  // The glm::intersectRayTriangle function returns true if an intersection occurs.
  // It also outputs the distance from the ray origin to the intersection point (t)
  // and the barycentric coordinates (u, v) of the intersection on the triangle.
    float t;
    float u, v;
    //  baryPosition, T& distance
    // vec<3, T, Q> const& orig, vec<3, T, Q> const& dir,    vec<3, T, Q> const& vert0, vec<3, T, Q> const& vert1, vec<3, T, Q> const& vert2, vec<2, T, Q>& baryPosition, T& distance
    glm::vec2 baryPosition;
    bool hit = glm::intersectRayTriangle(
        my_ray.origin,        // The ray's origin
        my_ray.direction,     // The ray's normalized direction
        v0, v1, v2,           // The three vertices of the triangle
        baryPosition,

        t // u, v               // Output parameters for the intersection details
    );

    // --- Step 6: Process the result ---
    if (hit) {
        // Calculate the world space intersection point using the ray's parametric equation:
        // P = Origin + Direction * t
        glm::vec3 intersection_point = my_ray.origin + my_ray.direction * t;

        //     std::cout << "Ray HIT the triangle!" << std::endl;
        //     std::cout << "Intersection Point: ("
         //        << intersection_point.x << ", "
         //        << intersection_point.y << ", "
         //        << intersection_point.z << ")" << std::endl;

             // int iNumVertsAlloc = AddIntersectionCube();


    }
    else {
        //    std::cout << "Ray DID NOT HIT the triangle. 4" << std::endl;
    }
    return baryPosition;

    //  return triangle;
      // return index
}



glm::vec2 checkMouseClick2(Ray my_ray,
    glm::vec3 v0,//(-1.0f, -1.0f, 0.0f),
    glm::vec3 v1,//(1.0f, -1.0f, 0.0f),
    glm::vec3 v2//(0.0f, 1.0f, 0.0f) 
    ,
    bool& Didhit,
    float& t2
)
{

    // --- Step 5: Perform the intersection test ---
  // The glm::intersectRayTriangle function returns true if an intersection occurs.
  // It also outputs the distance from the ray origin to the intersection point (t)
  // and the barycentric coordinates (u, v) of the intersection on the triangle.
    float t;
    float u, v;
    //  baryPosition, T& distance
    // vec<3, T, Q> const& orig, vec<3, T, Q> const& dir,    vec<3, T, Q> const& vert0, vec<3, T, Q> const& vert1, vec<3, T, Q> const& vert2, vec<2, T, Q>& baryPosition, T& distance
    glm::vec2 baryPosition;
    bool hit = glm::intersectRayTriangle(
        my_ray.origin,        // The ray's origin
        my_ray.direction,     // The ray's normalized direction
        v0, v1, v2,           // The three vertices of the triangle
        baryPosition,

        t // u, v               // Output parameters for the intersection details
    );
    Didhit = hit;
    t2 = t;
    // --- Step 6: Process the result ---
    if (hit) {
        // Calculate the world space intersection point using the ray's parametric equation:
        // P = Origin + Direction * t
        glm::vec3 intersection_point = my_ray.origin + my_ray.direction * t;

        //     std::cout << "Ray HIT the triangle!" << std::endl;
       //      std::cout << "Intersection Point: ("
         //        << intersection_point.x << ", "
       //          << intersection_point.y << ", "
        //         << intersection_point.z << ")" << std::endl;

             // int iNumVertsAlloc = AddIntersectionCube();


    }
    else {
        //   std::cout << "Ray DID NOT HIT the triangle. 5" << std::endl;
    }
    return baryPosition;

    //  return triangle;
      // return index
}


// https://shadered.org/view?s=3vnT8_GCl4 materialize
