PURPOSES:
	documentation of the viewer avatar
	templates for new viewer avatars
	tools for mesh attachment designers  

GENERAL INFORMATION:
The Second Life/OpenSim avatar definitions work in two primary modes, system avatar meshes and rigged mesh attachments. The differences are:
	The system avatar uses mesh morphs, which are not used for mesh attachments.
	The system avatar armature uses 19 bones; with vertex weighting defined in the viewer/Character/*.llm files. The two mEye bones are handled separately, in the code. On the other hand, each mesh attachment can use a maximum of 110 vertex bone groups from the 159 bone set; vertex weighting defined by the mesh designer. 
	The system avatar renders using normals and UV maps defined by the llm files. Mesh attachments use the designer's normal and UV mapping.

Both the system avatar and rigged mesh attachments use the "pos" values in viewer/Character/avatar_skeleton.xml for the Appearance shape sliders. Animations use the "pivot" values. The differences between "pos" and "pivot" are small.

As far as I know, all of the third party viewers are using the same Character folder at this time. The definitions are in the llm, xml and tga files in the folder. For the system avatar, this data has not changed in about 20 years. 

SYSTEM AVATAR REPLICA
There is a replica of the Second Life/OpenSim viewer avatar, SystemAvatarReplicaV1.1.blend, in this repo, constructed by Ada Radius aka Judith Adele, from data found in the viewer/Character/*.llm files, which were converted to txt and dae format by Kayaker Magic/Mike Higgins. The mesh is skinned to a replica of the armature (rig) as defined in viewer/Character/avatar_skeleton.xml. Mesh morphs, as defined in the llm files, are stored as shape keys in Blender, along with value ranges from viewer/Character/avatar_lad.xml

The llm files have different UV mapping for each of the mesh morphs. I didn't store them in this blend file, only the basemesh UV mapping for each piece. 

None of the tga file information is in yet; I haven't figured out how they should be represented in a useful way in Blender Materials. Or even if it's a good idea to spend a lot of time making sliders in Blender materials for images that very few users like. We probably need someone who is better than I am at Blender materials to work on it. 

There are almost certainly errors here, most likely in the form of automatic repairs by Blender to deal with asymmetries in the mesh data, the armature data, and particularly the vertex weighting data in the llm and xml files.

I have not included any work re unrigged prim or mesh attachments, as defined in avatar_lad.xml.  

SPREADSHEETS:
There are spreadsheets in this GitHub repo that I used to derive the sets of numbers to use in the Blender file. They are updated or replaced often - every time I work on this project. 

COMING SOON a Blender plugin by Owl Eyes aka Tom Ernst, that creates the data in Blender directly from the viewer Character data and viewer code, and includes the LOD data.  

last updated Ada RAdius 2023-07-17

TO DO:
Figure out the skeleton morph poses
Make materials with the tga files to replicate the inworld eye, hair and skin sliders. 