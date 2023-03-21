#include "ModelHandle.hpp"

using namespace GeneticModels;

ModelHandle::ModelHandle(GeneticModel* m) : model(m) { }

ModelHandle::ModelHandle(std::unique_ptr<GeneticModel>& m)
{ 
	model = std::move(m);
}

ModelHandle::ModelHandle(const GeneticModel& m) : model(m.clone()) { }

ModelHandle::ModelHandle(const ModelHandle& handle)
{
	model = std::move(std::unique_ptr<GeneticModel>(handle.model->clone()));
}

ModelHandle& ModelHandle::operator=(const ModelHandle& rhs)
{
	model = std::move(std::unique_ptr<GeneticModel>(rhs.model->clone()));
	return *this;
}

GeneticModel* ModelHandle::operator->() const
{
	return model.get();
}