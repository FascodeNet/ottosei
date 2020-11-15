#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <initializer_list>
using namespace std; 


int custom_exec_v(std::vector<std::string> args){
    char** argskun=NULL;
    argskun=new char*[args.size() + 2];
    for(size_t i=0;i<args.size();i++){
        argskun[i]=(char*)args[i].c_str();
    }
    argskun[args.size()]=NULL;
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        exit(-1);
    }else if(pid == 0){
        execvp(argskun[0],argskun);
        perror("exec");
        exit(-1);
    }
    int status;
    pid_t resultkun=waitpid(pid,&status,0);
    if(resultkun < 0){
        perror("waitpid error");
        exit(-1);
    }
    return status;
}
template<class... T> 
int custom_exec(T... args){
	std::vector<std::string> args_vector;
	for(string i : std::initializer_list<string>{args...}){
		args_vector.push_back(i);
	}
	return custom_exec_v(args_vector);
}
int custom_exec_v_no_wait(std::vector<std::string> args){
    char** argskun=NULL;
    argskun=new char*[args.size() + 2];
    for(size_t i=0;i<args.size();i++){
        argskun[i]=(char*)args[i].c_str();
    }
    argskun[args.size()]=NULL;
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        exit(-1);
    }else if(pid == 0){
        execvp(argskun[0],argskun);
        perror("exec");
        exit(-1);
    }
	return 0;
}
template<class... T> 
int custom_exec_no_wait(T... args){
	std::vector<std::string> args_vector;
	for(string i : std::initializer_list<string>{args...}){
		args_vector.push_back(i);
	}
	return custom_exec_v_no_wait(args_vector);
}
int main(int argc, char* argv[]) {
	bool h,m,l,g;
	const char* optstring = "hmlg";
	int opt;
	while((opt = getopt(argc, argv,optstring)) != -1) {
		switch(opt) {
		case 'h' :
			h = true;
			break;
		case 'm' :
			m = true;
			break;
		case 'l' :
			l = true;
			break;
		case 'g' :
			g = true;
			break;
		default :
			h = true;
		}
	}

	if(h || (m && l)) {
		printf ("ottosei: ottosei [OPTION]...\n"
			"Show an \"ottosei\" and play call of it.\n"
			"\"Ottosei\" is a Japanese words which means a fur seal.\n\n"
			"Options :\n"
			"	-m : Mute sound\n"
			"	-l : Play with louder sound\n"
			"	-g : Show an ottosei in GUI\n"
			"	-h : Help\n\n");

		return 0;
	}
	if(g){
		custom_exec_no_wait("display","/usr/share/serene/ottosei/ottosei.jpeg");
	}else{
		custom_exec("jp2a","/usr/share/serene/ottosei/ottosei.jpeg");
	}
	if(!m){
		if(l){
			return custom_exec("mpg123","-q","/usr/share/serene/ottosei/ottosei2.mp3");
		}else{
			return custom_exec("mpg123","-q","/usr/share/serene/ottosei/ottosei1.mp3");
		}
	}
	return 0;

	
}
