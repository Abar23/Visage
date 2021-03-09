

namespace Visage
{
    namespace Core
    {
        class MemoryManager
        {
            public:
                MemoryManager& GetInstance();

                

            private:
                MemoryManager();
                MemoryManager(const MemoryManager& manager) = delete;
                MemoryManager& operator=(const MemoryManager& manager) = delete;

                static MemoryManager* manager;

        };
    }
}