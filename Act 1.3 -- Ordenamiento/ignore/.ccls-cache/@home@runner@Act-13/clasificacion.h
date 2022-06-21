#pragma once
#include <vector>
#include "log.h"
#include <string>
class clasificacion
{
public:

	static std::vector<bitacora> monthBucketSort(std::vector<bitacora>); 
	static std::vector<bitacora> dayBucketSort(std::vector<bitacora>); 
    static std::vector<bitacora> hourBucketSort(std::vector<bitacora>); 
    static std::vector<bitacora> minuteBucketSort(std::vector<bitacora>); 
    static void secondBucketSort(std::vector<bitacora>&); 
    static void fullBucketSort(std::vector<bitacora>&); 
    static void swap(std::vector<bitacora>&,int,int); 
};