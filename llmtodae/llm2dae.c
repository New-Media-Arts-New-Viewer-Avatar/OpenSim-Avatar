    //program to read Linden Labs *.LLM (Linden Labs Binary Mesh 1.0) files
    //and convert them to DAE files
    //Making DAE files was NOT MY GOAL, so this process is incomplete
    //I'm ignoring the binormals, armature, weights and many other parts of the LLM
    //Usage:
    //llmdae file.llm > file.txt
    //llmdae -m Morph_name file.llm > file.txt
    //example:llmdae -m Male_Torso avatar_upper_body.llm >uppermale.txt 
    //2020-07-23 Kayaker Magic, aka Mike Higgins
    //Released under Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

float    f[256];        //buffers for reading various parts
char    s[2048];
unsigned short int    i[256];
unsigned long int    l[256];

#define    TITLE    24    //bytes in the heade that shay what am I
            //note: there is an extra byte after the nul,
            //I read it to get to the right spot in file

void trimFloat(float val)    //output a float as text with trailing 0s removed
{
    char out[256];
    sprintf(out," %12.6f",val);    //convert to float string
    char *ptr = out+strlen(out)-1;    //pointer to last character
    while (*ptr == '0')        //skip back over trailing 0s
        ptr -= 1;
    if (*ptr == '.')        //clobber the dot if it is the last character
        ptr -= 1;
    *(ptr+1)=0;            //terminate the string here
    ptr = out;
    while (*ptr == ' ')        //skip over the leading spaces
        ptr += 1;
    printf(" %s",ptr);        //and output the string
} //trimbloat

void printVec(float *fl,int count,int stride)    //print out a pile of floating point values
{
    int i;
    for (i=0;i<count;i++)
    {
        int j;
        for (j=0;j<stride;j++)
            trimFloat(*fl++);
    }
    printf("\n");        //break after last line
}

void addVec(float *from, float *to, int stride)    //add one vector to another
{
    int i;
    for (i=0;i<stride;i++)
    {
        *to = *to + *from++;
        to += 1;    //I don't trust the compiler to do this for me
    }
}

int main(int argc, char  *argv [ ])
{
    char *fname = argv[1];
    char *morph="not any known name";
    if (strcmp(fname,"-m")==0)    //if there is a morph name
    {
        morph = argv[2];    //remember that
        fname = argv[3];    //the file name follows
    }
    FILE *file = fopen(fname,"rb");
    if (file==NULL)
    {
        fprintf(stderr,"Can't open file %s\n",fname);
        return(1);
    }
    fread(s,TITLE,1,file);    //read the header
    if (strcmp(s,"Linden Binary Mesh 1.0")!=0)
    {
        printf("This file is not an LLM file! %s\n",fname);
        return(5);
    }
    int hasWeights=0;
    fread(&hasWeights,1,1,file);    //flag indicating if weights section is in file
    int hasDetailTexCoords=0;    //flag indicating if extra detailed texture section in file
    fread(&hasDetailTexCoords,1,1,file);
                //Note: I'm using numeric values instead of sizeof(float)
                //on purpose because that is how many bytes there are
                //in the file.
    fread(f,3,4,file);        //the position (always 0,9,0 for avatar meshes?)
    fread(f,3,4,file);        //the rotation angles always <0,0,0>
    int rotationOrder=0;
    fread(&rotationOrder,1,1,file);    //rotation order, always <0,0,0> 
    fread(f,3,4,file);        //scale, always <1,1,1>
    int numVertices=0;        //number of vertices
    fread(&numVertices,1,2,file);
//printf("number of vertices = %i\n",numVertices);
    float *verts=malloc(numVertices*3*sizeof(float));
    float *fptr=verts;
    int loop;    //read in all the vertices
    fread(verts,sizeof(float),3*numVertices,file);    //read all vertexes 
    float *norms=malloc(numVertices*3*sizeof(float));
    fread(norms,sizeof(float),3*numVertices,file);       //read one normal 
    for (loop=0;loop<numVertices;loop++)
    {
        fread(f,4,3,file);       //read one bi-normal and ignore it
    }
    float *texts=malloc(numVertices*3*sizeof(float));
    fread(texts,sizeof(float),2*numVertices,file);       //read one co-ord and print it out
    if (hasDetailTexCoords)
    {
        for (loop=0;loop<numVertices;loop++)
        {
            fread(f,4,2,file);       //read one co-ord and ignore them
        }
    }
    if (hasWeights)
    {
        for (loop=0;loop<numVertices;loop++)
        {
            fread(f,4,1,file);       //read one weight and ignore them
        }
    }
    int numFaces=0;
    fread(&numFaces,2,1,file);        //how many TRIANGLES
//printf("Number of Triangles: %i\n",numFaces);
    short *faces=malloc(numFaces*3*sizeof(short));
    fread(faces,sizeof(short),3*numFaces,file);    //just read them and save for the end
    int numSkinJoints=0;        //Skin Joints
    fread(&numSkinJoints,2,1,file);
    if (hasWeights)
    {
        s[64]=0;                //add an extra nul just in case
        for (loop=0;loop<numSkinJoints;loop++)
        {
            fread(s,64,1,file);
        }
    }
    while(fread(s,1,64,file)==64)
    {
        if (strcmp(s,"End Morphs")==0)
            break;
        int numMorphs=0;
        fread(&numMorphs,4,1,file);            //each named morph has some vertices
//        printf("    %s has %i targets\n",s,numMorphs);
        int vindex=0;
        for (loop=0;loop<numMorphs;loop++)
        {
            fread(&vindex,4,1,file);                     //each vertex has an index
            fread(f,4,11,file);                  //followed by 11 floats, a vector(3), normal(3), binomral(3) and UV(2)
            if (strcmp(s,morph)==0)    //if this is the one we want to apply
            {
                //hypotesis 1: each vector in the morph is ADDED to the target vertex
               //(my first hypothesis turned out to be correct! No need for #2)
                addVec(f,verts+vindex*3,3);
                addVec(f+3,norms+vindex*3,3);
//                addVec(f+9,texts+vindex*3,2);     //these cause nothing but trouble, I'm not morphine UV maps!
//                printf("      %4i:<%9.6f,%9.6f,%9.6f> <%9.6f,%9.6f,%9.6f> <%9.6f,%9.6f,%9.6f> (%9.6f,%9.6f)\n",
//                          vindex,f[0],f[1],f[2],f[3],f[4],f[5],f[6],f[7],f[8],f[9],f[10]);
            }
        }
    }
    //print them all out at the end
    int numFloats=numVertices*3;
            //*********first the header and the vertices*********************************
    printf("<?xml version='1.0' encoding='utf-8'?>\n\
<COLLADA xmlns='http://www.collada.org/2005/11/COLLADASchema' version='1.4.1' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'>\n\
  <asset>\n\
    <contributor>\n\
      <author>Kayaker Magic</author>\n\
      <authoring_tool>llm2dae</authoring_tool>\n\
    </contributor>\n\
    <created>2020-07-11</created>\n\
    <modified>2020-07-11</modified>\n\
    <unit name='meter' meter='1'/>\n\
    <up_axis>Z_UP</up_axis>\n\
  </asset>\n\
  <library_geometries>\n\
    <geometry id='Avatar-Test-mesh' name='Avatar-Test'>\n\
      <mesh>\n\
        <source id='Avatar-Test-mesh-positions'>\n\
          <float_array id='Avatar-Test-mesh-positions-array' count='%i'>\n\
",numFloats);
    printVec(verts,numVertices,3);
    printf("\n\
          </float_array>\n\
          <technique_common>\n\
            <accessor source='#Avatar-Test-mesh-positions-array' count='%i' stride='3'>\n\
              <param na:me='X' type='float'/>\n\
              <param name='Y' type='float'/>\n\
              <param name='Z' type='float'/>\n\
            </accessor>\n\
          </technique_common>\n\
        </source>\n\
",numVertices);
        //***************the normals****************************************
    printf("\n\n\
        <source id='Avatar-Test-mesh-normals'>\n\
          <float_array id='Avatar-Test-mesh-normals-array' count='%i'>\n\
",numFloats);
    printVec(norms,numVertices,3);
    printf("\n\
          </float_array>\n\
          <technique_common>\n\
            <accessor source='#Avatar-Test-mesh-normals-array' count='%i' stride='3'>\n\
              <param name='X' type='float'/>\n\
              <param name='Y' type='float'/>\n\
              <param name='Z' type='float'/>\n\
            </accessor>\n\
          </technique_common>\n\
        </source>\n\
",numVertices);
        //**********************the UV map**************************************
    int numUVs=numVertices*2;    //two floats per UV co-ord
    printf("\n\
        <source id='Avatar-Test-mesh-map-0'>\n\
          <float_array id='Avatar-Test-mesh-map-0-array' count='%i'>\n\
",numUVs);
    printVec(texts,numVertices,2);
    printf("\n\
          </float_array>\n\
          <technique_common>\n\
            <accessor source='#Avatar-Test-mesh-map-0-array' count='%i' stride='2'>\n\
              <param name='S' type='float'/>\n\
              <param name='T' type='float'/>\n\
            </accessor>\n\
          </technique_common>\n\
        </source>\n\
        <vertices id='Avatar-Test-mesh-vertices'>\n\
          <input semantic='POSITION' source='#Avatar-Test-mesh-positions'/>\n\
        </vertices>\n\
",numVertices);
        //*****************the triangle list (must be last, or Blender crashes!***********
    printf("\n\
        <triangles material='Material-material' count='%i'>\n\
          <input semantic='VERTEX' source='#Avatar-Test-mesh-vertices' offset='0'/>\n\
          <input semantic='NORMAL' source='#Avatar-Test-mesh-normals' offset='1'/>\n\
          <input semantic='TEXCOORD' source='#Avatar-Test-mesh-map-0' offset='2' set='0'/>\n\
          <p>\n\
",numFaces);
    short *sptr = faces;
    for (loop=0;loop<numFaces;loop++)
    {
        int j;
        for (j=0;j<3;j++)    //one triangle is 3 indexes
        {
                    //dae wants vertx #,normal #, map co-ore # which are identical here
                    //so I have to repeat each three times then there are 3 triples for a triangle
            printf(" %i %i %i",*sptr,*sptr,*sptr);    //index to vertex, normal, uv co-ord
            sptr += 1;
        }
    }
    printf("\n");    //make sure last line is terminated
    printf("\n\
          </p>\n\
        </triangles>\n\
      </mesh>\n\
    </geometry>\n\
  </library_geometries>\n\
\n");
        //*****************print the footer**********************************************
    printf("\n\
  <library_visual_scenes>\n\
    <visual_scene id='Scene' name='Scene'>\n\
      <node id='Camera' name='Camera' type='NODE'>\n\
        <matrix sid='transform'>0.6859207 -0.3240135 0.6515582 7.358891 0.7276763 0.3054208 -0.6141704 -6.925791 0 0.8953956 0.4452714 4.958309 0 0 0 1</matrix>\n\
        <instance_camera url='#Camera-camera'/>\n\
      </node>\n\
      <node id='Light' name='Light' type='NODE'>\n\
        <matrix sid='transform'>-0.2908646 -0.7711008 0.5663932 4.076245 0.9551712 -0.1998834 0.2183912 1.005454 -0.05518906 0.6045247 0.7946723 5.903862 0 0 0 1</matrix>\n\
        <instance_light url='#Light-light'/>\n\
      </node>\n\
      <node id='Avatar-Test' name='Avatar-Test' type='NODE'>\n\
        <matrix sid='transform'>1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1</matrix>\n\
        <instance_geometry url='#Avatar-Test-mesh' name='Avatar-Test'>\n\
          <bind_material>\n\
            <technique_common>\n\
              <instance_material symbol='Material-material' target='#Material-material'>\n\
                <bind_vertex_input semantic='UVMap' input_semantic='TEXCOORD' input_set='0'/>\n\
              </instance_material>\n\
            </technique_common>\n\
          </bind_material>\n\
        </instance_geometry>\n\
      </node>\n\
    </visual_scene>\n\
  </library_visual_scenes>\n\
</COLLADA>\n\
\n");


    fclose(file);
    return 0;
}




