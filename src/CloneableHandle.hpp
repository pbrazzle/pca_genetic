#ifndef CLONEABLE_HANDLE
#define CLONEABLE_HANDLE

#include "model/GeneticModel.hpp"

#include <memory>

namespace PCAGenetic
{
    template <typename T>
    class CloneableHandle
    {
        private:
			std::unique_ptr<T> handle;
			
		public:
			CloneableHandle(T* ptr) : std::unique_ptr<T>(ptr) { }
			CloneableHandle(std::unique_ptr<T>& ptr) { handle = std::move(ptr); }
			CloneableHandle(const T&) { handle = std::move(rhs->clone()); }
			CloneableHandle(const CloneableHandle<T>& rhs) { handle = std::move(rhs->clone()); }
			
			CloneableHandle& operator=(const CloneableHandle<T>& rhs) 
            {
                handle = std::move(rhs->clone());
                return *this;
            }
			
			T* operator->() const { return handle.get(); }
			T& operator*() const { return *handle; }
    };
}

#endif