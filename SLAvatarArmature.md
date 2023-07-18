Re the spreadsheet in this repository: avatar_skeletonXMLworksheet.ods, and SLArmatures.blend

Approximate history:
c.2002  the basemesh armature referred to in the llm files:
mPelvis, mTorso, mChest, mNeck, mHead, mEyeRight, mEyeLeft, mCollarLeft, mShoulderLeft, mElbowLeft, mWristLeft, mCollarRight, mWristRight, mHipRight, mKneeRight, mAnkleRight, mHipLeft, mKneeLeft, mAnkle Left. 

I'm not sure when or how they added mEyeLeft and mEyeRight in the code. They're not referred to in the llm files, which position one eye at 0,0,0. Those two bones are grouped (in avatar_skeleton.xml) as "Extra" along with mSkull, mFoot and mToe. 

With the arrival of rigged mesh attachments c. 2012, added bones: mSkull, mFootLeft, mFootRight, mToeLeft, mToeRight. 

2013 official support for collision volume weighting on rigged mesh attachments. It had already been in use by several rigged clothing designers for a few months. 

2015-2016 Project Bento - additional face, hand, spine, wing, tail, hind leg bones for mesh attachments. 

All of this data was released to Creative Commons licensing over a decade ago. Please see licensing information in the readme in this repository. 

GENERAL INFORMATION:
The Second Life/OpenSim avatar definitions work in two primary modes, system avatar meshes and rigged mesh attachments. The differences are:
	The system avatar uses mesh morphs, which are not used for mesh attachments.
	The system avatar armature uses 19 bones; with vertex weighting defined in the viewer/Character/*.llm files. The two mEye bones are handled separately, in the code. On the other hand, each mesh attachment can use a maximum of 110 vertex bone groups from the 159 bone set; vertex weighting defined by the mesh designer. 
	The system avatar renders using normals and UV maps defined by the llm files. Mesh attachments use the designer's normal and UV mapping.

Both the system avatar and rigged mesh attachments use the "pos" values in viewer/Character/avatar_skeleton.xml for the Appearance shape sliders. Animations use the "pivot" values. The differences between "pos" and "pivot" are small.

As far as I know, all of the third party viewers are using the same Character folder at this time. The definitions are in the llm, xml and tga files in the folder. For the system avatar, this data has not changed in about 20 years. 

IN THE BLEND FILE:

There are two armatures here: SystemAvatar and RiggedMeshAttachments. Mesh attachments are always going to be somewhat of a mismatch to the system avatar, because they're using different methods of morphing with the Appearance sliders. 

Here is a way to use RiggedMeshAttachments to export from Blender and into the viewer without a plugin. These settings may change with viewer and Blender upgrades.

Note that Blender rounds differently than the xml data, past the 5th place. 

Export:
Viewer mesh import limitations:
	no more than 110 vertex bone groups per object. Sometimes less. 
	no more than 4 bone weights per vertex
	no more than 8 materials per mesh
	no more than 21,844 triangles per material
	no more than 65,536 vertices per LOD for each mesh. Far less is better. 

1. Rotate the armature 90 degrees on the z axis, so it faces +X. The meshes should go with it, but if they don't, rotate them too. 
2. Select all, and apply all transforms. Check all of the pieces to make sure all the transforms got applied. Blender is a little buggy applying settings to more than one Object at a time. 
3. We need to have all the armature bones visible that are used in the vertex groups. Select the armature in Edit mode and in Pose mode, alt h to unhide any hidden bones. 
4. The mesh you want to export must be visible and selected. Hide any mesh you don't want to export to prevent accidentally including it. 
5. Export dae, with these settings:
	Preset: sl+opensim rigged
	Forward Axis Y, Up Axis Z. 
	Check: Selection Only, Include Armatures, Copy, Only Selected Map 
		Geom: up to you. I usually check Triangulate and Apply Modifiers but sometimes triangulating in Blender is better. 
		Armature: Deform Bones Only, Export to SL/OpenSim
		Extra: Keep Bind Info 
6. Import into the viewer. Under the rigging tab, check the box "Include Skin Weights", and leave "Include joint positions" unchecked. Unless you're making giant, weefolk or nonhumans and need to keep the joints fixed, then check it. This will disable the Appearance sliders that use the collision volumes. 

NOTE:

There are left-right asymmetries in the xml data, possibly deliberate. I left them in this version, not allowing Blender to automatically symmetrize them.

I set up pose mode bone groups, based on the avatar_skeleton.xml attribute "group=". Two of the colors; basemesh mBones, and collision bones, are based on the inworld bone displays (Developer/Avatar/Show Bones). I use these bone groups to make it easier to select bone groups. It's easy to change the colors to whatever you want. It's a little more work to put groups of bones into the armature layers, as Avastar does. Bento Buddy uses groups to organize bones in a different way, and handles the calculations to convert xml data to Blender data differently as well.   

Last updated Ada Radius 2023-07-17, Blender 3.6 LTS    

