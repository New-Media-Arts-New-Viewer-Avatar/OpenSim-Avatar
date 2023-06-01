	//File to read Linden Labs *.LLM (Linden Labs Binary Mesh 1.0) files
	//and dump them out converted to text
	//2020-07-21 Kayaker Magic, aka Mike Higgins

#include<stdio.h>
#include<math.h>
#include<string.h>

float	f[256];		//buffers for reading various parts
char	s[2048];
unsigned short int	i[256];
unsigned long int	l[256];

#define	TITLE	24	//bytes in the heade that shay what am I
			//note: there is an extra byte after the nul,
			//I read it to get to the right spot in file

void dumpfloat(char *name,float *f,int num)
{
    printf("%s",name);
    int loop;
    for (loop=0;loop<num;loop++)
        printf(" %12.6f",*f++);
    printf("\n");
} //dumpfloat

int main(int argc, char  *argv [ ])
{
    int loop;
    int numVertices=0;          //number of vertices

    printf("dump llm file: %s\n",argv[1]);
    FILE *ftr = fopen(argv[1],"rb");
    if (ftr==NULL)
    {
	fprintf(stderr,"Can't open file %s\n",argv[1]);
	return(1);
    }
    unsigned long pos = ftell(ftr);
    fread(s,TITLE,1,ftr);
    if (strcmp(s,"Linden Binary Mesh 1.0")!=0)
    {
	fprintf(stderr,"Not a Linden Binary Mesh 1.0\n");
	return(2);
    }
    printf("HEADER: %s\n",s);
    int flen=strlen(argv[1]);
    char basellm = argv[1][flen-6];		//an underscore in the file name
    if (basellm == '_')
	printf("This is an LOD file\n");	//means an LOD file
    else
	printf("This is a BASE file\n");
    pos = ftell(ftr);
    int hasWeights=0;
    fread(&hasWeights,1,1,ftr);	//flag indicating if weights section is in file
    printf("Has weights: %i\n",hasWeights);
    int hasDetailTexCoords=0;	//flag indicating if extra detailed texture section in file
    fread(&hasDetailTexCoords,1,1,ftr);
    printf("Has Detail Tex Coords: %i\n",hasDetailTexCoords);
				//Note: I'm using numeric values instead of sizeof(float)
				//on purpose because that is how many bytes there are
				//in the file.
    fread(f,3,4,ftr);		//the position (always 0,0,0 for avatar meshes?)
    dumpfloat("Position:",f,3);
    fread(f,3,4,ftr);		//the rotation angles
    dumpfloat("Rotation:",f,3);
    int rotationOrder=0;
    fread(&rotationOrder,1,1,ftr);	//rotation order
    printf("Rotation Order: %i\n",rotationOrder);
    fread(f,3,4,ftr);		//scale
    dumpfloat("Scale:   ",f,3);
    if (basellm != '_')		//only base files have the following sections
    {
    pos =ftell(ftr);
    fread(&numVertices,1,2,ftr);
    printf("%04lx:Number of Vertices: %i\n:%04lx:\n",pos,numVertices,ftell(ftr));
    for (loop=0;loop<numVertices;loop++)
    {
	fread(f,4,3,ftr);	//read one vertex and print it out
	printf(" <%9.6f,%9.6f,%9.6f>",f[0],f[1],f[2]);
	if ((loop%4)==3)		//every so often
	    printf("\n");	//break the line
    }
    printf("\nNormals: %06lx:\n",ftell(ftr));
    for (loop=0;loop<numVertices;loop++)
    {
        fread(f,4,3,ftr);       //read one normal and print it out
        printf(" <%9.6f,%9.6f,%9.6f>",f[0],f[1],f[2]);
        if ((loop%4)==3)                //every so often
            printf("\n");       //break the line
    }
    printf("\nBinormals: %06lx:\n",ftell(ftr));
    for (loop=0;loop<numVertices;loop++)
    {
        fread(f,4,3,ftr);       //read one normal and print it out
        printf(" <%9.6f,%9.6f,%9.6f>",f[0],f[1],f[2]);
        if ((loop%4)==3)                //every so often
            printf("\n");       //break the line
    }
    printf("\nTexture Coords: %08lx:\n",ftell(ftr));
    for (loop=0;loop<numVertices;loop++)
    {
        fread(f,4,2,ftr);       //read one co-ord and print it out
        printf(" <%9.6f,%9.6f>",f[0],f[1]);
        if ((loop%6)==5)                //every so often
            printf("\n");       //break the line
    }
    printf("\nDetail Texture Coords: %08lx:\n",ftell(ftr));
    if (hasDetailTexCoords)
    {
        for (loop=0;loop<numVertices;loop++)
        {
            fread(f,4,2,ftr);       //read one co-ord and print it out
            printf(" <%9.6f,%9.6f>",f[0],f[1]);
            if ((loop%6)==5)                //every so often
                printf("\n");       //break the line
        }
    }
    else
        printf("    NONE.");
    printf("\nWeights: %08lx:\n",ftell(ftr));
    if (hasWeights)
    {
        for (loop=0;loop<numVertices;loop++)
        {
            fread(f,4,1,ftr);       //read one weight and print it out
            printf(" %9.6f",f[0]);
            if ((loop%12)==11)                //every so often
                printf("\n");       //break the line
        }
    }
    else
        printf("    NONE.");
    } //end this is a base llm
	//even LOD files have a list of trianges
    pos=ftell(ftr);
    int numFaces=0;
    fread(&numFaces,2,1,ftr);		//how many TRIANGLES
    printf("\n%08lx:Number of Triangles: %i \n%08lx:\n",pos,numFaces,ftell(ftr));
    for (loop=0;loop<numFaces;loop++)
    {
	fread(i,2,3,ftr);		//each face is three vertexes
	printf(" (%4i,%4i,%4i)",i[0],i[1],i[2]);
        if ((loop%6)==5)                //every so often
            printf("\n");       //break the line
    }
    if (basellm != '_')		//only base llm file have the following sections
    {
    pos = ftell(ftr);
    int numSkinJoints=0;	//Skin Joints
//    fread(&numSkinJoints,2,1,ftr);
//    printf("\n%08lx:Number of Skin Joints: %i\n%08lx:\n",pos,numSkinJoints,ftell(ftr));
    if (hasWeights)
    {
    fread(&numSkinJoints,2,1,ftr);
    printf("\n%08lx:Number of Skin Joints: %i\n%08lx:\n",pos,numSkinJoints,ftell(ftr));

	s[64]=0;		//add an extra nul just in case
	for (loop=0;loop<numSkinJoints;loop++)
	{
	    fread(s,64,1,ftr);
	    printf("    %s\n",s);
	}
    }
    printf("Morph Section:\n");
    pos = ftell(ftr);
    while(fread(s,1,64,ftr)==64)
    {
	if (strcmp(s,"End Morphs")==0)
	{
	    printf("    %s\n",s);
	    break;
	}
	fread(&numVertices,4,1,ftr);		//each named morph has some verticies
	printf("    %s has %i target_vertex,vertex,normal,binormal,uv at %08lx\n",s,numVertices,ftell(ftr));
///	printf("    %s has %i target_vertices at %08lx\n",s,numVertices,ftell(ftr));
	int vindex=0;
	for (loop=0;loop<numVertices;loop++)
	{
	    fread(&vindex,4,1,ftr);			//each vertex has an index
	    fread(f,4,11,ftr);			//followed by 11 floats, a vector(3), normal(3), binomral(3) and UV(2)
	    printf("      %4i:<%9.6f,%9.6f,%9.6f> <%9.6f,%9.6f,%9.6f> <%9.6f,%9.6f,%9.6f> (%9.6f,%9.6f)\n",
			vindex,f[0],f[1],f[2],f[3],f[4],f[5],f[6],f[7],f[8],f[9],f[10]);
	}
    }
    pos = ftell(ftr);
    int numRemaps=0;
    fread(&numRemaps,4,1,ftr);
    printf("%08lx:Vertex Remap Section has %i remaps\n%08lx:\n",pos,numRemaps,ftell(ftr));
    for (loop=0;loop<numRemaps;loop++)
    {
	int src=0;
	int dst=0;
	fread(&src,4,1,ftr);		//why did they switch to 32bit ints?
	fread(&dst,4,1,ftr);
	printf(" (%4i,%4i)",src,dst);
	if ((loop%10)==9)
	    printf("\n");
    }
    } //end of base LLM sections
    printf("\nI think I'm done...\n");
    fclose(ftr);
    return 0;
}




