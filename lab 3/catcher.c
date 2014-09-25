/*
Author: David Greenberg
Lab #3
Lab_Name: Catcher
*/
#define maxTerm 3
#define SIG_ERR (void (*)()) -1
#define SIG_DEFAULT (void(*)()) 0
#define SIG_IGNORE (void(*)()) 1
#define SIG_TERM 15

#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

//typedef
typedef void (*sighandler_t)(int);

//Prototypes
int get_signal_value(char*);
void createHandlers(int, char**);
char* signal_term(int);
void handler(int);
time_t getCurrentTime();
int ngStrcomp(char*, char*);

//Main Function
int main(int argv, char** argc){
	fprintf(stderr, "catcher: $$ = %d\n", (int)getpid());
	createHandlers(argv, argc);
	return 0;
}

//Create the signal handlers
void createHandlers(int numberSignals, char** currentArrays){
	signal(SIGTERM,handler);	
	//Create the handlers	
	while (*currentArrays != NULL){
		if ((signal(get_signal_value(*currentArrays++), handler)) == SIG_ERR){
			//Error found, throw error
			perror("ERROR: Could not create Signal Handler");
		}
	}

	//Pause until something causes a kill
	while (1){
		pause();
	}
}

//Function called when signal is recieved
void handler(int signalValue){
	//Create new signal creater
	sighandler_t phandler = signal(signalValue, handler);

	//Create the static value	
	static int count_terms = 0;
	static int total_signal_count = 0;
	//Increase number of signals caught
	total_signal_count++;
	//Print SIGTERM caught at 1234(time)
	fprintf(stderr,"%s caught at %d\n", signal_term(signalValue), (int)getCurrentTime());
	//Increment if term, else reset
	if (signalValue == SIG_TERM){
		count_terms++;
		//End function if enough terms recieved
		if(count_terms==3){
			fprintf(stderr,"catcher: Total signals count = %d\n",total_signal_count);
			exit(0);
		}	
	}
	else{
		count_terms = 0;
	}

	
		
}

time_t getCurrentTime(){
	int current_time = time(NULL);

	if (current_time == ((time_t)-1)){
		(void)fprintf(stderr, "Failure to compute the current time");
		return -1;
	}

	return current_time;
}

//Return the integer value of the signal
int get_signal_value(char* signalName){
	if (ngStrcomp("SIGINT", signalName) == 0){
		return SIGINT;
	}
	else if (ngStrcomp("HUP", signalName) == 0){
		return SIGHUP;
	}
	else if (ngStrcomp("QUIT", signalName) == 0){
		return SIGQUIT;
	}
	else if (ngStrcomp("KILL", signalName) == 0){
		return SIGKILL;
	}
	else if (ngStrcomp("TRAP", signalName) == 0){
		return SIGTRAP;
	}
	else if (ngStrcomp("IOT", signalName) == 0){
		return SIGIOT;
	}
	else if (ngStrcomp("BUS", signalName) == 0){
		return 7;
	}
	else if (ngStrcomp("FPE", signalName) == 0){
		return 8;
	}
	else if (ngStrcomp("KILL", signalName) == 0){
		return 9;
	}
	else if (ngStrcomp("USR1", signalName) == 0){
		return 10;
	}
	else if (ngStrcomp("SEGV", signalName) == 0){
		return 11;
	}
	else if (ngStrcomp("USR2", signalName) == 0){
		return 12;
	}
	else if (ngStrcomp("PIPE", signalName) == 0){
		return 13;
	}
	else if (ngStrcomp("ALRM", signalName) == 0){
		return 14;
	}
	else if (ngStrcomp("TERM", signalName) == 0){
		return 15;
	}
	else if (ngStrcomp("STKFLT", signalName) == 0){
		return 16;
	}
	else if (ngStrcomp("CHLD", signalName) == 0){
		return 17;
	}
	else if (ngStrcomp("CONT", signalName) == 0){
		return 18;
	}
	else if (ngStrcomp("STOP", signalName) == 0){
		return 19;
	}
	else if (ngStrcomp("TSTP", signalName) == 0){
		return 20;
	}
	else if (ngStrcomp("TTIN", signalName) == 0){
		return 21;
	}
	else if (ngStrcomp("TTOU", signalName) == 0){
		return 22;
	}
	else if (ngStrcomp("URG", signalName) == 0){
		return 23;
	}
	else if (ngStrcomp("XCPU", signalName) == 0){
		return 24;
	}
	else if (ngStrcomp("XFSZ", signalName) == 0){
		return 25;
	}
	else if (ngStrcomp("VTALRM", signalName) == 0){
		return 26;
	}
	else if (ngStrcomp("PROF", signalName) == 0){
		return 27;
	}
	else if (ngStrcomp("WINCH", signalName) == 0){
		return 28;
	}
	else if (ngStrcomp("IO", signalName) == 0){
		return 29;
	}
	else if (ngStrcomp("PWR", signalName) == 0){
		return 30;
	}

}

char* signal_term(int signalNumber){
	switch (signalNumber){
	case 1:
		return "SIGHUP";
		break;
	case 2:
		return "SIGINT";
		break;
	case 3:
		return "SIGQUIT";
		break;
	case 4:
		return "SIGKILL";
	case 5:
		return "SIGTRAP";
		break;
	case 6:
		return "SIGIOT";
		break;
	case 7:
		return "SIGBUS";
		break;
	case 8:
		return "SIGFPE";
		break;
	case 9:
		return "SIGKILL";
		break;
	case 10:
		return "SIGUSR1";
		break;
	case 11:
		return "SIGSEGV";
		break;
	case 12:
		return "SIGUSR2";
		break;
	case 13:
		return "SIGPIPE";
		break;
	case 14:
		return "SIGALRM";
		break;
	case 15:
		return "SIGTERM";
		break;
	case 16:
		return "SIGSTKFLT";
		break;
	case 17:
		return "SIGCHLD";
		break;
	case 18:
		return "SIGCONT";
		break;
	case 19:
		return "SIGSTOP";
		break;
	case 20:
		return "SIGTSTP";
		break;
	case 21:
		return "SIGTTIN";
		break;
	case 22:
		return "SIGTTOU";
		break;
	case 23:
		return "SIGURG";
		break;
	case 24:
		return "SIGXCPU";
		break;
	case 25:
		return "SIGXFSZ";
		break;
	case 26:
		return "SIGVTALRM";
		break;
	case 27:
		return "SIGPROF";
		break;
	case 28:
		return "SIGWINCH";
		break;
	case 29:
		return "SIGIO";
		break;
	case 30:
		return "SIGPWR";
		break;
	default:
		return "ERROR";
	}


}

//Compare two strings
int ngStrcomp(char* s, char* t){
	int i;
	for (i = 0; s[i] == t[i]; i++){
		if (s[i] == '\0')
			return 0;

	}

	return s[i] - t[i];

}
