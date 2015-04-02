#include <iostream>
#include <thread>
#include <vector>
#include <math.h> 
#include <chrono>
using namespace std;
static const int num_threads = 16;
static const int log_num_threads=(int)round(log2(num_threads));
int SUM_ARR[num_threads]={0};



   class Thread_data {
   	  int  thread_id;
	public:
	  Thread_data() {}
	  Thread_data(int id) {this->thread_id=id;}
	  void set_id(int id) {this->thread_id=id;}
	  int get_id() {return this->thread_id;}
	};

std::vector<Thread_data> Tdata_vec;


    //This function will be called from a thread

    void SubsetSum(int taskid) {
	auto i=0;
	auto taskid2=taskid;
        auto sum2=0;
 	int binaryNumber[log_num_threads]={0};
	
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	
	 for(i=0; i<log_num_threads; i++){
         	binaryNumber[i]= taskid % 2;
         	taskid = taskid / 2;
    	 }
	 for(i=0; i<log_num_threads; i++){
		sum2+=binaryNumber[i]*Tdata_vec[i].get_id();
  	   }

        std::cout << "Thread " << taskid2 <<", With sum:"<< sum2 <<"\n"<< std::endl;
	 SUM_ARR[taskid2]=sum2;
    }

   int main() {
	Tdata_vec.push_back(1);
	Tdata_vec.push_back(2);
	Tdata_vec.push_back(-3);
	Tdata_vec.push_back(6);


	std::thread t[num_threads];
	for (int i = 0; i < num_threads; ++i) {
            t[i] = std::thread(SubsetSum, i);
        }

	        //Join the threads with the main thread
        for (int i = 0; i < num_threads; ++i) {
            t[i].join();
        }


	std::cout <<"\n SUM_ARR:"<<std::endl;
	for(auto t=0; t<num_threads; t++){
	   std::cout <<SUM_ARR[t]<<std::endl;
	}
	std::cout <<"\n"<<std::endl;



	for(auto t=0; t<num_threads; t++){
		if (SUM_ARR[t]==3) printf("Number 3 was found!\n");
	}

        return 0;


   }
