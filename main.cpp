#include <Fir1.h>
#include <sox.h>
#include <iostream>
#include <vector>
#include <audioio.h>


int main(int argc, char *argv[]){
	
	const double sr {96000}, fl {0.3}, ss {4.9}, lrate {0.002};
	
        int nc = int(fl*sr);
        int ns = int(sr*ss);
	
	AudioReader wet(argv[1]); 
	AudioReader dry(argv[2]);
        
        std::vector<double> src;
        while(!wet.eof()){
		src.push_back(wet.get());    
        }
        
        std::vector<double> training;
        while(!dry.eof()){
		training.push_back(dry.get());    
        }
        
        print(size(src) + " " + size(training))
        
        pclose
}
