#include "BuildingPoint.h"




BuildingPoint  BuildingPoint::getObject(vector<string> param,string sepOut) {
	BuildingPoint buildPoint(param,sepOut);
	return buildPoint;
}

vector<BuildingPoint> BuildingPoint::getObjectSet(vector<vector<string>> param,string sepOut) {
	vector<BuildingPoint> buildingPointSet;
	vector<vector<string>>::iterator iter = param.begin();
	while(iter!=param.end()) {
		BuildingPoint buildingPoint = BuildingPoint::getObject(*iter++,sepOut);
		buildingPointSet.push_back(buildingPoint);
	}
	return buildingPointSet;
}