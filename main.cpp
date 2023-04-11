#include <Fir1.h>
#include <sox.h>
#include <iostream>
#include <vector>
#include <audioio.h>
#include <sstream>
#include <stdio.h>

int main(int argc, char *argv[]){
	
	const double sr {96000}, fl {0.3}, ss {4.9}, lrate {0.002};
	
        int nc = int(fl*sr);
        int ns = int(sr*ss);
	
	AudioReader wet(argv[1]); 
	AudioReader dry(argv[2]);
        
        std::vector<double> src;
	int i {0};
	while(!wet.eof())
	{
		if(i>=ns)
			vout.push_back(src.get());
		i++;
	}
        
        std::vector<double> training;
        i=0;
        while(!dry.eof()){
        	if(i>=ns)
			training.push_back(dry.get());
		i++;    
        }
        
        std::cout<<size(src)<<" "<<size(training)<<'\n';
        
        Fir1 fir(nc);
        int fnum {1};
        double sum {0);
        
        for(i=0;i<size(src);i++)
        	sum = sum + src[i] *src[i];
        double msi = sum / size(src);
        
        bool ok {true};
        if(size(src)!=size(training))
        {
        	ok=false;
        	std::cout<<"interference and source samples are different lengths"<<'\n';
        }
        
        if(ok)
        {
        	const int trial=sr*2;
        	std::cout<<"Pre-training..."<<'\n';
        	
        	if(trial<size(src))
        		for(i=0;i<trial;i++)
        			fir.lms_update(src[i]-fir.filter(training[i]));
        	else
        		for(i=0;i<size(src);i++)
				fir.lms_update(src[i]-fir.filter(training[i]));
				
		std::cout<<"Processing..."<<'\n';        	
        	
        	std::vector<double> error;
        	for(i=0;i<size(training);i++)
        	{
        		error.push_back(src[i] - fir.filter(training[i]));
        		fir.lms_update(error[i]);
        	}
        	
        	sum=0;
        	for(i=0;i<size(error);i++)
        		sum=sum+error[i]*error[i];
        	double power_gain = sum/msi;
        	std::cout<<"Power gain: "<<power_gain<<'\n';
        	
        	for(i=0;i<size(src);i++)
        	{
        		std::stringstream sso;
        		sso << src[i] << std::endl;
        		std::string cmdo("sox '" + argv[3] + "' -t wav -c 1 -");
        		pipeo = popen(cmdo.c_str(), "r"); 
        		fputs(sso.str().c_str(), pipeo);
        	}
        }
        	
}
