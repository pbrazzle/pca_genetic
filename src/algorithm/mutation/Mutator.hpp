#ifndef MUTATOR
#define MUTATOR

class Mutator
{
	public:
		virtual ~Mutator() { }
	
		//Mutates the given parameters
		//Returns a copy of the mutated parameters
		virtual std::vector<double> mutateParams(std::vector<double> params) = 0;
};

#endif