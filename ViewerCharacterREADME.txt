This is a replica of the Second Life/OpenSim viewer avatar, defined in the viewer Character folder. As far as I know, all of the third party viewers are using the same Character folder at this time. The definitions are in the llm, xml and tga files in the folder, and for the viewer system avatar, have not changed in about 20 years.

Purposes: documentation and testing of the viewer avatar. Templates for new viewer avatars.  

The blend file has a draft of a replica of the llm basemesh components, skinned to a replica of the armature (rig) as defined in avatar_skeleton.xml. Not the same values as the armature used by mesh attachments, which are also stored in avatar_skeleton.xml. Mesh morphs from the llm files, along with ranges (Appearance sliders) from avatar_lad.xml are replicated via Blender shape keys. I'm still working on how to replicate the param_skeleton values in Blender. 

The llm files have different UV mapping for each of the mesh morphs. I didn't store them in this blend file, only the basemesh UV mapping for each piece. 

None of the tga file information is in yet; I haven't figured out how they should be represented in a useful way in Blender Materials. Or even if it's a good idea to spend a lot of time making sliders in Blender materials for images that very few users like. We probably need someone who is better than I am at Blender materials to work on it. 

There are almost certainly errors here, most likely in the form of automatic repairs by Blender to deal with asymmetries in the mesh data, the armature data, and particularly the vertex weighting data in the llm and xml files. 

Mike Higgins, aka Kayaker Magic, converted the llm files to a readable format, from which I took the numbers I needed, and to dae files that I uploaded to Blender to make the base mesh and shape keys. 

There is a spreadsheet in this GitHub repo that I used to derive the sets of numbers to use in the Blender file. It gets updated every time I work on this project. 

last updated 2023-06-22 Judith Adele aka Ada Radius 

TO DO:
We need a coder to work on converting Blender data or exports back to llm. Frank-Thomas Ernst aka Owl Eyes is working on it from time to time, Mike Higgins also. 
Finish the skeleton morph poses in the armature.
Make materials with the tga files to replicate the inworld eye, hair and skin sliders. 