#include "ModelHandle.hpp"

using namespace GeneticModels;

ModelHandle::ModelHandle(GeneticModel* m) : model(m) { }

ModelHandle::ModelHandle(const ModelHandle& handle)
{
	model = std::move(std::unique_ptr<GeneticModel>(handle.model->clone()));
}

ModelHandle& ModelHandle::operator=(const ModelHandle& rhs)
{
	model = std::move(std::unique_ptr<GeneticModel>(rhs.model->clone()));
	return *this;
}

GeneticModel* ModelHandle::operator->()
{
	return model.get();
}