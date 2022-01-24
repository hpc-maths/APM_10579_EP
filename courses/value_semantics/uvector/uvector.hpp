#ifndef UVECTOR_HPP
#define UVECTOR_HPP

namespace hpc
{
    class uvector
    {
    public:

        uvector(size_t = 0);
        uvector(size_t size, double value);

    private:

        double* p_data;
        size_t m_size;
    };
}

#endif
