// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) \
	if (GEngine)    \
	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text)
#include "Boxer.h"

// Sets default values
ABoxer::ABoxer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABoxer::BeginPlay()
{
	Super::BeginPlay();
	LoadProgress("test.txt");
	//randomizeWeights();
}

void ABoxer::SetPosition(const int index, const FVector _position)
{
	position[index] = _position;
}

void ABoxer::SetVelocity(const int index, const FVector _velocity)
{
	velocity[index] = _velocity;
}

// void ABoxer::SetOrientationalVectors(const int index, const FVector _forwardVector, const FVector _rightVector, const FVector _upVector)
// {
// 	forwardVector[index] = _forwardVector;
// 	rightVector[index] = _rightVector;
// 	upVector[index] = _upVector;
// }

FVector ABoxer::GetForce(const int index)
{
	return force[index];
}

void ABoxer::randomizeWeights()
{
	srand((unsigned int)time(NULL));

	for (size_t i = 0; i < 12996; i++)
	{
		InputLayerToFirstHiddenLayerWeight[i] = 2 * (rand() / (float)RAND_MAX) - 1;
		if (i < 6498)
			FirstHiddenLayerToSecondHiddenLayerWeight[i] = 2 * (rand() / (float)RAND_MAX) - 1;
		if (i < 3249)
			SecondHiddenLayerToOutputWeight[i] = 2 * (rand() / (float)RAND_MAX) - 1;
	}
}

void ABoxer::SaveProgress(const char *filename)
{
	char path[MAX_PATH];
	GetFullPathName(filename, MAX_PATH, path, nullptr);
	char buf[(12996 + 6498 + 3249) * 11];
	FILE *file;
	std::ifstream saveweights;
	fopen_s(&file, fullPath, "w"); // weights

	if (file)
	{
		epoch >> saveweights;
		for (size_t i = 0; i < 12996; i++)
		{
			InputLayerToFirstHiddenLayerWeight[i] >> saveweights;
		}
		"\n" >> saveweights;

		for (size_t i = 0; i < 6498; i++)
		{
			FirstHiddenLayerToSecondHiddenLayerWeight[i] >> saveweights;
		}
		"\n" >> saveweights;

		for (size_t i = 0; i < 3249; i++)
		{
			SecondHiddenLayerToOutputWeight[i] >> saveweights;
		}
	}
}

bool ABoxer::LoadProgress(const char *filename)
{
	// line 1: epoch
	// epoch =
	// then: InputLayerToFirstHiddenLayerWeight (sep=" ")
	// then: FirstHiddenLayerToSecondHiddenLayerWeight
	// then: SecondHiddenLayerToOutputWeight

	// attempt 1
	//FString projectPath = FPaths::ProjectDir();
	//std::string fullPath = std::string(TCHAR_TO_UTF8(*projectPath)) + "Source/BoxerAI/" + filename;
	// const char *path = fullPath.c_str();
	// char *userPath = nullptr;
	
	// attempt 2
	// size_t sz = 0;
	// std::string path;
	// if (_dupenv_s(&userPath, &sz, "USER") == 0 && userPath != nullptr)
	// {
	// 	path = userPath;
	// 	free(userPath);
	// 	path += "Documents\\Unreal Projects\\Boxing-AI\\Source\\BoxerAI\\";
	// 	path += filename;
	// }

	// attempt 3
	// CoInitialize(NULL);
    // TCHAR* path = 0;
    // SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_SIMPLE_IDLIST, NULL, &path);
	// _bstr_t b(path);
	// const char* OMG = b;
	// std::string mobOfTheDeadGameplay = OMG;
	// mobOfTheDeadGameplay += "Documents\\Unreal Projects\\Boxing-AI\\Source\\BoxerAI\\";
	// mobOfTheDeadGameplay += filename;
    // CoTaskMemFree(path);

	// attempt 4
	// system("echo %cd% > pathForUE4.txt");

	// attempt 5
	// std::string localPath = ("C:/Users/melon/Documents/Unreal Projects/Boxing-AI/Source/BoxerAI/");
	// localPath += filename;
	// const char* fullPath = localPath.c_str();

	// attempt 6 (What! is it this easy :[ )
	char path[MAX_PATH];
	GetFullPathName(filename, MAX_PATH, path, nullptr);

	// update: attempt 5 came out in Chinease, because it was UTF8, solved it with UTF8_TO_TCHAR
	
	// if (GEngine)
	// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("path %s"), UTF8_TO_TCHAR(angest)));

	char buf[(12996 + 6498 + 3249) * 11];
	FILE *file;
	fopen_s(&file, fullPath, "r"); // weights
	if (file)
	{
		int layer = 0;
		size_t i = 0;
		while (fgets(buf, sizeof(buf), file))
		{
			// reads one word at a time, seperate by a newline, and places it at buf[0] with a trailing '\0'

			if (buf[i] == '\n' && buf[i+1] == '\0')
			{
				layer++;
				i = 0;
				continue;
			}

			std::string word = buf;
			float w = std::stof(word);

			switch (layer)
			{
			case 0:
				InputLayerToFirstHiddenLayerWeight[i++] = w;
				break;
			case 1:
				FirstHiddenLayerToSecondHiddenLayerWeight[i++] = w;
				break;
			case 2:
				SecondHiddenLayerToOutputWeight[i++] = w;
				break;

			default:
				// no thank you
				break;
			}
		}
		free(buf);
	}
}

void ABoxer::CalculateOutput()
{
	float inputs[114];
	for (int i = 0; i < 114; i++)
	{
		inputs[i] = 0;
	}

	for (size_t i = 0; i < sizeof(inputs) / sizeof(*inputs); i += 6)
	{
		inputs[i] = position[i].X;
		inputs[i + 1] = position[i].Y;
		inputs[i + 2] = position[i].Z;

		inputs[19 + i] = velocity[i].X;
		inputs[19 + i + 1] = velocity[i].Y;
		inputs[19 + i + 2] = velocity[i].Z;
	}

	float firstWeightSum[114];
	for (size_t i = 0; i < 114; i++)
	{
		firstWeightSum[i] = 0;
	}

	for (size_t i = 0; i < 2 / 3.0 * ((19 * 3 + 19 * 3) + 57); i++)
	{
		for (size_t j = 0; j < 2 / 3.0 * ((19 * 3 + 19 * 3) + 57); j++)
		{
			firstWeightSum[i] += inputs[j] * InputLayerToFirstHiddenLayerWeight[i * 114 + j];
		}
	}

	float secondWeightSum[57];
	for (size_t i = 0; i < 57; i++)
	{
		secondWeightSum[i] = 0;
	}

	for (size_t i = 0; i < 2 / 3.0 * ((19 * 3 + 19 * 3) + 57); i++)
	{
		for (size_t j = 0; j < 1 / 3.0 * ((19 * 3 + 19 * 3) + 57); j++)
		{
			secondWeightSum[i] += firstWeightSum[j] * FirstHiddenLayerToSecondHiddenLayerWeight[i * 57 + j];
		}
	}

	float finalWeightSum[57];
	for (size_t i = 0; i < 57; i++)
	{
		finalWeightSum[i] = 0;
	}

	for (size_t i = 0; i < 1 / 3.0 * ((19 * 3 + 19 * 3) + 57); i++)
	{
		for (size_t j = 0; j < 1 / 3.0 * ((19 * 3 + 19 * 3) + 57); j++)
		{
			finalWeightSum[i] += secondWeightSum[j] * SecondHiddenLayerToOutputWeight[i * 57 + j];
		}
	}

	for (size_t i = 0; i < 1 / 3.0 * ((19 * 3 + 19 * 3) + 57); i += 3)
	{
		force[i / 3].X = finalWeightSum[i];
		force[i / 3].Y = finalWeightSum[i + 1];
		force[i / 3].Z = finalWeightSum[i + 2];
	}

	// if (!LoadProgress())
	// {
	// 	std::ofstream savedweights;
	// 	std::string epochString = "" + epoch;
	// 	savedweights.open(epochString.c_str());
	

	// 	for (size_t i = 0; i < sizeof(InputLayerToFirstHiddenLayerWeight) / sizeof(*InputLayerToFirstHiddenLayerWeight); i++)
	// 	{
	// 		savedweights << InputLayerToFirstHiddenLayerWeight[i] << "\n";
	// 	}
	// 	savedweights << "\n";
	// 	for (size_t i = 0; i < sizeof(FirstHiddenLayerToSecondHiddenLayerWeight) / sizeof(*FirstHiddenLayerToSecondHiddenLayerWeight); i++)
	// 	{
	// 		savedweights << FirstHiddenLayerToSecondHiddenLayerWeight[i] << "\n";
	// 	}

	// 	savedweights << "\n";

	// 	for (size_t i = 0; i < sizeof(SecondHiddenLayerToOutputWeight) / sizeof(*SecondHiddenLayerToOutputWeight); i++)
	// 	{
	// 		savedweights << SecondHiddenLayerToOutputWeight[i] << "\n";
	// 	}

	// 	savedweights << std::endl;
	// }
}

// Called every frame
void ABoxer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalculateOutput();

	if (GEngine)
	{
	}
}
