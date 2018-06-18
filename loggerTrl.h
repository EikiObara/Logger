#ifndef __LOGGER_TRL_H__
#define __LOGGER_TRL_H__

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>

#include <sys/stat.h>
#include <sys/types.h>

//#include "Eigen/Core"

namespace Trl{


class Logger{
private:
	std::string fileName;
	std::string date;
	std::ostringstream stack;
public:
	Logger(){
		stack.str("");
	}

	Logger(const std::string name){
		fileName = name;
	}

	std::string TimeStamp(void){
		std::time_t result = std::time(nullptr);
		std::ostringstream timeName;
	
	#ifdef __linux__
		std::tm *pnow = std::localtime(&result);
		timeName << pnow->tm_year + 1900 << "_" << pnow->tm_mon + 1 << pnow->tm_mday
			<< "_" << pnow->tm_hour << pnow->tm_min << pnow->tm_sec;
	#elif _WIN32
		std::tm pnow;
		localtime_s(&pnow,&result);
		timeName << pnow.tm_year + 1900 << "_" << pnow.tm_mon + 1 << pnow.tm_mday
			<< "_" << pnow.tm_hour << pnow.tm_min << pnow.tm_sec;
	#else
		std::tm *pnow = std::localtime(&result);
	#endif

		return std::string(timeName.str());
	}

	std::string DateStamp(void){
		std::time_t result = std::time(nullptr);
		std::ostringstream timeName;
	
	#ifdef __linux__
		std::tm *pnow = std::localtime(&result);
		timeName << pnow->tm_year + 1900 << "_" << pnow->tm_mon + 1 << pnow->tm_mday;
	#elif _WIN32
		std::tm pnow;
		localtime_s(&pnow,&result);
		timeName << pnow.tm_year + 1900 << "_" << pnow.tm_mon + 1 << pnow.tm_mday;
	#else
		std::tm *pnow = std::localtime(&result);
	#endif

		return std::string(timeName.str());
	}

	//ex.) call in destractor... (please run when the terminate job)
	void Write(){
		if(fileName.size() < 1){
			std::cout << "*** file name no setting ***" << std::endl;
			std::cout << "*** cannot output data   ***" << std::endl;
		}

		std::string file = "./log";
		struct stat st;			//ディレクトリ存在確認用構造体

		if(stat(file.c_str(), &st) != 0){
				mkdir(file.c_str(),0775);
				return;
		}
		
		std::string dateFile = "./log/" + DateStamp();

		if(stat(dateFile.c_str(), &st) != 0){
				mkdir(dateFile.c_str(),0775);
				return;
		}

		std::string path;

		std::string bufFile = dateFile + "/"  + TimeStamp();

		mkdir(bufFile.c_str(),0775);
		
		path = bufFile + "/" + fileName + ".txt";

		std::ofstream ofs(path,std::ios::out);
		ofs << stack.str() << std::endl;
	}

	void SetFileName(const std::string name){
		fileName = name;	
	}
	//void SetData(Eigen::MatrixXd data);
	template <typename T> void SetData(const T data, const int num){
		for(int i = 0; i < num; ++i){
   			stack << data[i];
   			stack << "\t";
   		}
		
		stack << std::endl;
	}

	template <typename T> void SetData(const std::vector<T> data){
		for(int i = 0, n = data.size(); i < n; ++i){
			stack << data[i] << "\t";
		}
		stack << std::endl;
	}

	template <typename T> void SetSentence(const T data){
		stack << data << std::endl;
	}
};

//void Logger::SetData(Eigen::MatrixXd data){
//	for(int i = 0; i < data.rows();++i){
//		for(int j = 0; j < data.cols(); ++j){
//			stack << data(i,j) << "\t";
//		}
//		stack << std::endl;
//	}
//}



}	//namespace Trl

#endif //__LOGGER_TRL_H__
