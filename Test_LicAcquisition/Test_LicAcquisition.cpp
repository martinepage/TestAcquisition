// Test_LicAcquisition.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <string>
#include <iostream>
#include <list>
#include <NativeExport_CppCliWrapper_LicApi.h>


using namespace std;

 class DoAcquisitionRun
{
	struct FeatureType
	{
		string name;
		int initialCount;
		int increment;
		int delay;
	};

private:
	string _productName;
	string _Version;
	string _DeviceID;
	list<FeatureType> _featureList;
	NativeExport_CppCliWrapper_LicApi *m_pLicensing = nullptr;
	ClientInputParameters *m_pClientInputParameters = nullptr;
	const LicAcquisitionFeatureStatusType *m_pFeatureListStatus = nullptr;

	
public:
	DoAcquisitionRun()
	{

	}
	
	bool ParseFeatureData(const string featureData)
	{
		int idx1 = featureData.find_first_of(':');
		FeatureType f;
		f.name = featureData.substr(0,idx1);

		idx1++;
		int idx2 = featureData.find_first_of(',', idx1);
		string initialCount = featureData.substr(idx1, idx2 - idx1);
		f.initialCount = stoi(initialCount);
		idx1 = idx2 + 1;

		idx2 = featureData.find_first_of(',', idx1);
		string increment = featureData.substr(idx1, idx2 - idx1);
		f.increment = stoi(increment);
		idx1 = idx2 + 1;

		idx2 = featureData.find_first_of(',', idx1);
		string delay = featureData.substr(idx1, idx2 - idx1);
		f.delay = stoi(delay);

		return true;
	}

	bool ParseArguments(int argc, const char *argv[])
	{
		
		bool DoneParsing = false;
		bool error = false;
		int state = 0;
		int finalstate = 8;
		int argNum = 1;

		
		while (argv[argNum])
		{
			string option;
			option = argv[argNum];

			if (option.compare("-p") == 0)
			{
				argNum++;
				_productName = argv[argNum];
				
			}
			else if (option.compare("-f") == 0)
			{
				argNum++;
				string featureData;
				featureData = argv[argNum];
				bool status = ParseFeatureData(featureData);
			}
			else if (option.compare("-v") == 0)
			{
				argNum++;
				_Version = argv[argNum];
			}
			else if (option.compare("-d") == 0)
			{
				argNum++;
				_DeviceID = argv[argNum];
			}

			argNum++;
		}

		return true;
	}

	bool RegisterLicensingSubsystem()
	{
		bool bStatus = false;
		if (m_pLicensing)
		{
			bStatus = m_pLicensing->ResetLicenseRequestInfo();
		}
		else
		{
			if (m_pLicensing = new NativeExport_CppCliWrapper_LicApi())
			{
				int errCode = 0;
				if (m_pLicensing->LoadLibraries(errCode))
				{
					if (m_pLicensing->CreateClientConnection())
					{
						return true;
					}
				}
			}
			return false;
		}
		return bStatus;

	}

};

int main(int argc, const char *argv[])
{
	int errCode = 0;
	DoAcquisitionRun acqRun;
	bool atatus = acqRun.ParseArguments(argc, argv);

	string ArgumentList;

    std::cout << "Hello World!\n"; 
}
