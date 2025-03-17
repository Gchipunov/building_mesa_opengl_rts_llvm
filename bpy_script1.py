import bpy;

python

Collapse

Wrap

Copy
import bpy
from math import radians

# Ensure we're in Object mode initially
bpy.ops.object.mode_set(mode='OBJECT')

# Get the armature object (replace 'Armature' with your armature's name if different)
armature = bpy.data.objects.get('Armature')
if not armature:
    print("No armature found! Please create an armature named 'Armature'")
else:
    # Select the armature
    bpy.context.view_layer.objects.active = armature
    armature.select_set(True)

    # Switch to Pose mode to move the bone
    bpy.ops.object.mode_set(mode='POSE')

    # Get the bone by name (replace 'Bone' with your bone's name)
    bone = armature.pose.bones.get('Bone')
    if not bone:
        print("Bone not found! Please check the bone name")
    else:
        # Method 1: Move bone using location (in bone's local space)
        bone.location = (0.0, 0.0, 1.0)  # Moves bone 1 unit along Z axis
        
        # Method 2: Rotate bone (uncomment to use)
        # bone.rotation_euler = (radians(45), 0.0, 0.0)  # Rotates 45 degrees around X axis
        
        # Method 3: Move using matrix (uncomment to use)
        # from mathutils import Matrix
        # translation = Matrix.Translation((0.0, 0.0, 1.0))
        # bone.matrix = translation @ bone.matrix

    # Optional: Add a keyframe if in an animation
    frame_number = 1
    bone.keyframe_insert(data_path="location", frame=frame_number)
    # bone.keyframe_insert(data_path="rotation_euler", frame=frame_number)  # For rotation

    # Switch back to Object mode
    bpy.ops.object.mode_set(mode='OBJECT')

    print("Bone movement complete!")
