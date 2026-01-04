
#include "Create-Spawn_Packet-Sender.h"


// https://www.youtube.com/watch?v=ov4tZlamOBA

CreateSpawnPacketSender::CreateSpawnPacketSender()
{
    p_gCreateSpawnPacketSender = this;


}

CreateSpawnPacketSender::~CreateSpawnPacketSender()
{

}

void CreateSpawnPacketSender::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{


    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {

        SendNewBox(g_pBuildStructure_Cube->placement_position.x, g_pBuildStructure_Cube->placement_position.y, g_pBuildStructure_Cube->placement_position.z);
    }




}

void CreateSpawnPacketSender::SendNewBox(float x, float y, float z)
{
    long long waitBetweenSequencePackets = 100;
    int client_id_udp = GetClientID(); // move this to a GameCoordinator Class, and a API AllainceAndAllegenceID class
    int selected_cube_id_udp = 1; // fix the raytrace detection, by adding to more objects

    int client_id = client_id_udp; // GetClientID, flag_COMMAND_REFRESH_UDP_ID
    int object_id = selected_cube_id_udp; // selected_cube_client_id, selected_cube_server_id
    std::cout << " CreateSpawnPacketSender::SendNewBox(float x, float y, float z):" << std::endl;
    std::cout << "x " << x << "y " << y << "z " << z << std::endl;
    // exit(0);

    BuildCommand buildcommand;

    buildcommand.object_id = 1;
    buildcommand.position.x = x;
    buildcommand.position.y = y;
    buildcommand.position.z = z;
    buildcommand.sequence_number = 1;


    MessageHeader header;
    header.type = BUID_COMMAND;
    header.size = sizeof(Cube);

    //   send_message_udp_queue(header, (const char*)&buildcommand);
    send_message_udp_queue_queue(header, (const char*)&buildcommand);

    std::this_thread::sleep_for(std::chrono::milliseconds(waitBetweenSequencePackets));

    buildcommand.object_id = 1;
    buildcommand.position.x = x;
    buildcommand.position.y = y;
    buildcommand.position.z = z;
    buildcommand.sequence_number = 2;


    //  MessageHeader header;
    header.type = BUID_COMMAND;
    header.size = sizeof(Cube);

    //  send_message_udp_queue(header, (const char*)&buildcommand);
    send_message_udp_queue_queue(header, (const char*)&buildcommand);

    std::this_thread::sleep_for(std::chrono::milliseconds(waitBetweenSequencePackets));

    buildcommand.object_id = 1;
    buildcommand.position.x = x;
    buildcommand.position.y = y;
    buildcommand.position.z = z;
    buildcommand.sequence_number = 3;


    //  MessageHeader header;
    header.type = BUID_COMMAND;
    header.size = sizeof(Cube);

    //  send_message_udp_queue(header, (const char*)&buildcommand);
    send_message_udp_queue_queue(header, (const char*)&buildcommand);
}


CreateSpawnPacketSender* p_gCreateSpawnPacketSender = 0;
