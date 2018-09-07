#ifndef __LOGGER_TRL_H__
#define __LOGGER_TRL_H__

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <sys/stat.h>
#include <sys/types.h>

#include "stamper.hpp"
//#include "Eigen/Core"

namespace Trl{

class Logger{
public:
	Logger(){
		stack.str("");
		homeFolder = TimeStamp() + "_" + DateStamp();
	}

	Logger(const std::string name){
		stack.str("");
		SetFileName(name);
		homeFolder = TimeStamp() + "_" + DateStamp();
	}

	//ex.) call in destractor... (please run when the terminate job)
	void Write(std::string folderName = ""){
		if(fileName.size() < 1){
			std::cout << "*** file name no setting ***" << std::endl;
			std::cout << "*** cannot output data   ***" << std::endl;
		}

		std::string file = "./log";
		IsExistDirectory(file);

		std::string dateFolder = file + "/" + DateStamp();
		IsExistDirectory(dateFolder);

		std::string examFolder = dateFolder + "/" + homeFolder;
		IsExistDirectory(examFolder);

		std::string timeFolder;

		if(folderName.size() > 1){
			timeFolder = examFolder + "/" + folderName;
		}else{
			timeFolder = examFolder + "/" + TimeStamp();
		}
		IsExistDirectory(timeFolder);
		
		std::string path = timeFolder + "/" + fileName + ".dat";

		std::ofstream ofs(path,std::ios::out);
		ofs << stack.str() << std::endl;

		stack.str("");	//格納変数クリア
		stack.clear(std::stringstream::goodbit);
	}

	void SetFileName(const std::string name){
		fileName = name;	
	}

	//void SetData(Eigen::MatrixXd data);
	template <typename T> void SetData(const T data, const int num){
		for(int i = 0; i < num; ++i)	stack << data[i] << "\t";
		stack << std::endl;
	}

	template <typename T> void SetData(const std::vector<T> data){
		for(int i = 0, n = data.size(); i < n; ++i)	stack << data[i] << "\t";
		stack << std::endl;
	}

	template <typename T> void SetSentence(const T data){
		stack << data << std::endl;
		EndLine();
	}

private:
	std::string fileName;
	std::string homeFolder;
	std::ostringstream stack;

	void IsExistDirectory(std::string file){
		struct stat st;			//ディレクトリ存在確認用構造体
		if(stat(file.c_str(), &st) != 0){
				mkdir(file.c_str(),0775);
		}
	}

	void EndLine(){
		stack << std::endl;
	}
};

}	//namespace Trl

#endif //__LOGGER_TRL_H__
