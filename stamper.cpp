
#include "stamper.hpp"

#include <ctime>
#include <sstream>
#include <iomanip>

std::string TimeStamp(void){
	std::time_t result = std::time(nullptr);
	std::ostringstream timeName;

#ifdef __linux__
	std::tm *pnow = std::localtime(&result);
	timeName << std::setfill('0') << std::setw(2) << pnow->tm_hour<< "_" << pnow->tm_min << "_" << pnow->tm_sec;
#elif _WIN32
	std::tm pnow;
	localtime_s(&pnow,&result);
	timeName << std::setfill('0') << std::setw(2) << pnow.tm_hour << "_" << pnow.tm_min << "_" << pnow.tm_sec;
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
	timeName << pnow->tm_mon + 1 << "_" << pnow->tm_mday << "_" << pnow->tm_year + 1900;
#elif _WIN32
	std::tm pnow;
	localtime_s(&pnow,&result);
	timeName << pnow.tm_mon + 1 << "_" << pnow.tm_mday << "_" << pnow.tm_year + 1900;
#else
	std::tm *pnow = std::localtime(&result);
#endif

	return std::string(timeName.str());
}

