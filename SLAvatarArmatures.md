This data comes from viewer/Character/avatar_skeleton.xml. The male versions are a hack using data from avatar_lad.xml

Approximate history:
c.2002  the basemesh armature, pos value, referred to in the llm files:
mPelvis, mTorso, mChest, mNeck, mHead, mEyeRight, mEyeLeft, mCollarLeft, mShoulderLeft, mElbowLeft, mWristLeft, mCollarRight, mWristRight, mHipRight, mKneeRight, mAnkleRight, mHipLeft, mKneeLeft, mAnkle Left. 

I'm not sure when or how they added mEyeLeft and mEyeRight. They're not referred to in the llm files, which position one eye at 0,0,0. Those two bones are grouped as "Extra" along with mSkull, mFoot and mToe. 

With the arrival of mesh attachments c. 2012, additions mSkull, mFootLeft, mFootRight, mToeLeft, mToeRight, and pivot values - more decimal places. Note that Blender rounds differently than the xml data, past the 5th place. 

2013 official support for collision volume weighting on rigged mesh attachments. It had already been in use by several rigged clothing designers for a few months. The collision bones continue to use "pos" values.  

2015-2016 Project Bento - additional face, hand, spine, wing, tail, hind leg bones. These have both pivot and pos values listed in the xml data, but only pivot values, AFAIK, are used in the mesh attachments themselves. None of them are used in the system avatar.   

All of this data was released to Creative Commons licensing over a decade ago. Please see licensing information in the readme in this repository. 

IN THIS FILE:

SL_Armature_pos is also included in the SLViewerReplica.blend file, and is useful if you're having problems fitting a mesh attachment to the system avatar and want to see more of what might be going on. Mesh attachments are always going to be somewhat of a mismatch to the system avatar, because they're using different armatures. Most designers put better vertex weighting into the mesh attachments, and hide the system avatar if it clips. The system avatar vertex weighting is particularly odd at the shoulders, because of the way it is calculated in the viewer/Character/*.llm files. 

SL_Armature_pivot is for mesh attachments. I sell it with mesh for system avatars, and give it away here.

Here is a way to use SL_Armature-pivot to export from Blender and into the viewer without a plugin. These settings may change with viewer and Blender upgrades.

Export:
Viewer mesh import limitations:
	no more than 110 vertex bone groups per object. Sometimes less. 
	no more than 4 bone weights per vertex
	no more than 8 materials per mesh
	no more than 21,844 triangles per material
	no more than 65,536 vertices per LOD for each mesh. Far less is better. 

1. Rotate the armature 90 degrees on the z axis, so it faces +X. The meshes should go with it, but if they don't, rotate them too. 
2. Select all, and apply all transforms. Check all of the pieces to make sure all the transforms got applied. Blender is a little buggy applying settings to more than one Object at a time. 
3. We need to have all the armature bones visible. Select the armature in Edit mode and in Pose mode, alt h to unhide any hidden bones. 
4. The mesh you want to export must be visible and selected. Hide any mesh you don't want to export to prevent accidentally including it. 
5. Export dae, with these settings:
	Preset: sl+opensim rigged
	Forward Axis Y, Up Axis Z. 
	Check: Selection Only, Include Armatures, Copy, Only Selected Map 
		Geom: up to you. I usually check Triangulate and Apply Modifiers but sometimes triangulating in Blender is better. There are several methods.  
		Armature: Deform Bones Only, Export to SL/OpenSim
		Extra: Keep Bind Info 
6. Import into the viewer. Under the rigging tab, check the box "Include Skin Weights", and leave "Include joint positions" unchecked. Unless you're making giant, weefolk or nonhumans and need to keep the joints fixed, then check it. This will disable the Appearance sliders that use the collision volumes. 
7. If you are importing for a male and having problems then, back in Blender, reskin your mesh to the female armature and re-export. 

NOTE:

There are left-right asymmetries in the xml data, possibly deliberate. I left them in this version, not allowing Blender to automatically symmetrize them.

I set up pose mode bone groups, based on the avatar_skeleton.xml attribute "group=". Two of the colors; basemesh mBones, and collision bones, are based on the inworld bone displays (Developer/Avatar/Show Bones). I use these bone groups to make it easier to select bone groups. It's easy to change the colors to whatever you want. A little more work to put groups of bones into the armature layers, as Avastar does. Bento Buddy uses groups to organize bones in a different way, and handles the calculations to convert xml data to Blender data differently as well.   

Last updated Ada Radius 2023-06-04, Blender 3.3.6 LTS    

