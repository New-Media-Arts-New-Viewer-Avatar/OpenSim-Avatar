Workflow notes:
Software used: Blender, Notepad, XML Notepad, LibreOffice Calc

Import Mike Higgin's (Kayaker Magic) llm-to-dae conversion mesh files into Blender files, for for each mesh part and its morphs.

Rename to the morphs names, both Object and Mesh in Blender.

Create a collection for each set, so we can see the count and compare to the llm-To-dae folders.

Rotate to face front and apply rotations. 

Start a new Blend file, load morph mesh collections. Append Head first so eyelashes will be labeled as .001. They share morphs. 

Name UV maps for each mesh piece - avatar_eye, avatar_hair, avatar_head, avatar_eyelashes, avatar_upper_body, avatar_lower_body, avatar_skirt so they'll show up in the dae export correctly.

Make shape keys:
Don't make any changes to the basemesh pieces or indices will change, and no longer match those in the llm files. Don't add modifiers, change normals. Fixing the UV map asymmetries doesn't change the vertex indices. It's possible to fix the indices with a plugin but it's a PITA. 

These two plugins are useful when using this replica as a template for new viewer Characters: Mesh: Shape Key Transfer by Ajit D'Monte (fBlah) and System: Shape Key Manger Pro by Cody Winchester (codywinch) 

Select morph object, then basemesh object, Object data panel/Shape Keys, down arrow, Join As Shapes

For testing: input Value_Min, Value_Max from avatar_lad.xml morphs. Name= is how llm reads the avatar_lad file. param are the mesh morphs. 

Input vertex groups and vertex weights from the values in the llm files - see my spreadsheet worksheets. There are significant weights asymmetries in Hair and Lower_Body and I let Blender fix them as I went. I used this plugin to select ranges of indices for weighting from the llm numbers: Mesh:Select vertex by index by GilaDD

Build armature from the joints listed in the llm files, using avatar_skeleton.xml pos values. Blender will automatically symmetrize.

Consider replicating the asymmetries? bleh. 

Clear Blender bone roll, not used in the llm files. 

Bind mesh pieces to the new armature. 

Before exporting to dae:
Set each shape key to base mesh and each value to zero. 
Export each basemesh as dae with these settings:
Main:
	Selection Only
	Include Armatures
	Include Shape Keys
Geom: Transform Decomposed
Armature: Deform Bones Only
Animations: Uncheck
Extra: Uncheck all

note: 
In Blender, bone length, in Pose mode is always on the Y axis. 

TO DO:
We need a coder to work on converting Blender data or exports back to llm. Frank-Thomas Ernst aka Owl Eyes is working on it from time to time, Mike Higgins aka Kayaker Magic, also. 

param_skeleton morphs - conversion to Blender. Not needed for the llm conversion. 

Make materials with the tga files to replicate the inworld eye, hair and skin sliders. 

