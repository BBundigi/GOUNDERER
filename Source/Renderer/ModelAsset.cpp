#include <cassert>
#include <fstream>
#include <vector>
#include "ModelAsset.h"

void ModelAsset::Load(const std::string& InPath)
{

	std::vector<Vector4> VertPositions;
	std::vector<UINT> IndexPositions;

	std::vector<Vector2> VertUVs;
	std::vector<UINT> IndexUVs;

	std::vector<Vector3> VertNormals;
	std::vector<UINT> IndexNormals;

	std::ifstream Fin(InPath, std::ios::in);
	assert(Fin.is_open());
	while (true)
	{
		std::string CurLine;
		Fin >> CurLine;

		if (Fin.eof() || Fin.bad() || Fin.fail())
		{
			break;
		}
		else if (CurLine == "v")
		{
			float x, y, z;
			Fin >> x >> y >> z;
			Vector4 CurPos = Vector4(x, y, z, 1);
			VertPositions.emplace_back(CurPos);
		}
		else if (CurLine == "vt")
		{
			float x, y;
			Fin >> x >> y;
			Vector2 CurUV = Vector2(x, y);
			VertUVs.emplace_back(CurUV);
		}
		else if (CurLine == "vn")
		{
			float x, y, z;
			Fin >> x >> y >> z;
			Vector3 CurNormal = Vector3(x, y, z);
			VertNormals.emplace_back(CurNormal);
		}
		else if (CurLine == "f")
		{
			std::string CurDataString;
			UINT CurDataSet[3];

			for (int i = 0; i < 3; ++i)
			{
				Fin >> CurDataString;
				char* cStr = new char[CurDataString.length() + 1];
				strcpy(cStr,CurDataString.c_str());
				char* token = strtok(cStr,"/");
				int j = 0;
				while (token != NULL)
				{
					unsigned int value;
					sscanf(cStr, "%u", &CurDataSet[j]);
					j++;
					token = strtok(NULL,"/");
				}
				delete[] cStr;
				IndexPositions.emplace_back(CurDataSet[0]);
				IndexUVs.emplace_back(CurDataSet[1]);
				IndexNormals.emplace_back(CurDataSet[2]);
			}
		}
	}
	assert(IndexPositions.size() == IndexUVs.size() && IndexUVs.size() == IndexNormals.size());

	mVerticesLength = mIndicesLength = IndexPositions.size();

	mVertices = std::make_unique<Vertex[]>(mVerticesLength);
	mIndices = std::make_unique<UINT[]>(mIndicesLength);
	for (int i = 0; i < IndexPositions.size(); ++i)
	{
		mVertices[i] =  Vertex(VertPositions[IndexPositions[i] - 1], 
			VertNormals[IndexNormals[i] - 1] ,
			VertUVs[IndexUVs[i] - 1]);
		mIndices[i] = i;
	}
}
