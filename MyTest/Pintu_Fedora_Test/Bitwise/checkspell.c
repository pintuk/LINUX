#include<stdio.h>
#include<stdlib.h>
#include<string.h>


    char *misspelt_words_accuracy[] = {"abraod", "accesion", "acordance", "acieved", "additonal", "admiistered", "ambulence", "aand", "apolgies", "apperently", "appropriat", "apprpriate", "arguements", "assigmments", "assiciated", "asociation", "atending", "avaiable", "avilable", "baiscally", "bloked", "braching", "bradcast", "bulletings", "camara", "capabiltes", "catakoguing", "cataloguin", "challange", "characterissing", "cisting", "coeffcient", "cofficient", "collecyting", "commitee", "commenest", "comporable", "compariosns", "complementary", "connecton", "conservatie", "contins", "controll", "converzely", "cooperqtion", "corresond", "councelling", "critisisms", "decresing", "definate", "degredation", "dependant", "desireble", "desparate", "detailled", "deveoop", "differnt", "distibution", "odne", "eaxh", "effeiciency", "elimiation", "eminating", "netry", "invironment", "examiniation", "excede", "exta", "facilites", "fairlu", "fassion", "irst", "fisrtly", "foreseeable", "funcional", "genral", "govermental", "hanbook", "heuritics", "homr", "howver", "ilustrate", "immediatly", "importnat", "impractible", "increasinly", "independance", "individula", "indidual", "innefficient", "infromation", "instal", "internationlly", "interprte", "interuption", "invlving", "juridiction", "lagre", "lenght", "libraies", "likelyhood", "lits", "lsits", "logarihm", "mainenance", "maniputaltation", "maenas", "modiefied", "molcular", "omve", "nedded", "netowrks", "numbeer", "obvios", "occassional", "ommissions", "poerator", "oredr", "ouput", "overcomming", "overhaed", "particualar", "periferal", "phlology", "peices", "possibilty", "potentialy", "practictioner", "preuming", "prioities", "probabally", "pronlem", "proceure", "procesing", "produts", "provid", "quesionnaire", "radiuss", "reactioos", "reasinably", "redecoraton", "rference", "referrred", "regsirties", "relable", "repititious", "represntatives", "recources", "resing", "retentiaon", "revenu", "satsfactory", "scaned", "seaarch", "salected", "sepaphore", "seprate", "simialirty", "similarily", "sixze", "slighlty", "sofware", "spaekers", "stnadard", "stetemets", "stratigically", "structrue", "structurs", "substantal", "succede", "uggested", "synshronise", "tequniques", "thrir", "thwre", "thses", "thhis", "threee", "tollerance", "trafic", "ransmission", "unecessary", "usueal", "vectore", "waitng", "wgich", "whic", "wondrful", "wouls"};
	
    char *ref_corrections_accuracy[] = {"abroad", "accession", "accordance", "achieved", "additional", "administered", "ambulance", "and", "apologies", "apparently", "appropriate", "appropriate", "arguments", "assignments", "associated", "association", "attending", "available", "available", "basically", "blocked", "branching", "broadcast", "bulletins", "camera", "capabilities", "cataloguing", "cataloguing", "challenge", "characterising", "casting", "coefficient", "coefficient", "collecting", "committee", "commonest", "comparable", "comparisons", "complementary", "connection", "conservative", "contains", "control", "conversely", "cooperation", "correspond", "counselling", "criticisms", "decreasing", "definite", "degradation", "dependent", "desirable", "desperate", "detailed", "develop", "different", "distribution", "done", "each", "efficiency", "elimination", "emanating", "entry", "environment", "examination", "exceed", "extra", "facilities", "fairly", "fashion", "first", "firstly", "forseeable", "functional", "general", "governmental", "handbook", "neuritis", "home", "however", "illustrate", "immediately", "important", "impracticable", "increasingly", "independence", "individual", "individual", "inefficient", "information", "install", "internationally", "interpret", "interruption", "involving", "jurisdiction", "large", "length", "libraries", "likelihood", "list", "lists", "logarithm", "maintenance", "manipulation", "means", "modified", "molecular", "move", "needed", "networks", "number", "obvious", "occasional", "omissions", "operator", "order", "output", "overcoming", "overhead", "particular", "peripheral", "philology", "pieces", "possibility", "potentially", "practitioner", "presuming", "priorities", "probably", "problem", "procedure", "processing", "products",  "provide", "questionnaire", "radius", "reactions", "reasonably", "redecoration", "reference", "referred", "registries", "reliable", "repetitious", "representatives", "resources", "resting", "retention", "revenue", "satisfactory", "scanned", "search", "selected", "seashore", "separate", "similarity", "similarly", "size", "slightly", "software", "speakers", "standard", "statements", "strategically", "structure", "structures", "substantial", "succeed", "suggested", "synchronize", "techniques", "their", "there", "theses", "this", "three", "tolerance", "traffic", "transmission", "unnecessary", "usual", "vector", "waiting", "which", "which", "wonderful", "would"};

char *misspelt_words_basic[] = {"acieved","aand", "loev", "camara"};


#define		min(a,b)	( (a) < (b) ) ? (a) : (b)
					


int diff(char x, char y)
{
	if(x == y) return(0);
	else
	return(1);
}

void PrintTable(int m, int n, int E[][100])
{
	int i = 0; int j = 0;

	for(i=0; i<=m; i++)
	{
		for(j=0; j<=n; j++)
		{
			printf("%5d",E[i][j]);
		}
		printf("\n");
	}
}


int Knapsack_Edit(int m, int n, char *x, char *y, char *substr)
{
	int E[1024][1024];
	int i = 0; int j = 0; int k = 0;

	for(i=0; i<=m; i++)
	{
		E[i][0] = i;
	}
	for(j=1; j<=n; j++)
	{
		E[0][j] = j;
	}

	for(i=1; i<=m; i++)
	{
		for(j=1; j<=n; j++)
		{
			E[i][j] = min( min(E[i-1][j]+1, E[i][j-1]+1), (E[i-1][j-1] + diff(x[i-1],y[j-1])) );
			if( (x[i-1] == y[j-1]) && (strchr(substr,x[i-1]) == NULL) )
			{
				substr[k++] = x[i-1];
			}
		}
	}
	substr[k] = '\0';
	//PrintTable(m, n, E);
	return(E[m][n]);
}


main()
{
	int n = 0; int m = 0;
	int i = 0; int j = 0;
	char string1[100]; char string2[100]; char matchstr[100];
	int maxdist = 0; int len = 0;

	//memset(matchstr,'\0',sizeof(matchstr));
	//printf("Enter a string sequence 1:-\n");
	//scanf("%s",string1);
	//printf("Enter a string sequence 2:-\n");
	//scanf("%s",string2);

	//m = strlen(string1);
	//n = strlen(string2);
	int no_words_accuracy  = sizeof(misspelt_words_accuracy)/sizeof(char *);
	int no_words_basic = sizeof(misspelt_words_basic)/sizeof(char *);

	for(i=0; i<no_words_accuracy; i++) {
		maxdist = Knapsack_Edit(m, n, string1, string2, matchstr);
		printf("Max Distance = %d\n",maxdist);
		printf("matched chars are:-\n");
		len = strlen(matchstr);
		for(i=0; i<len; i++)
		{
			printf("%c  ",matchstr[i]);
		}
	}
	printf("\n");
}

