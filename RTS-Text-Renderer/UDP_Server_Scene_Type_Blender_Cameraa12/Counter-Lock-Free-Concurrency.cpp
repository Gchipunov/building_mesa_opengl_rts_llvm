
#include "Counter-Lock-Free-Concurrency.h"

// Lock Free design 
// https://www.youtube.com/watch?v=kPh8pod0-gk // 23:00
// https://github.com/CppCon/CppCon2024/blob/main/Presentations/When_Lock-Free_Still_Isn't_Enough.pdf
// 23:00 Time in Video of Code
// https://danielanderson.net/

struct Counter {

    bool increment_if_not_zero() {
        auto current = counter.load();
        //"CAS Loop" Compare-Exchange loop

                // * The so-called "CAS loop" (compare and swap loop) us the bread and butter of lock-free
                // algorithms and data structures
                //      * Read the current state of the data structure
                //      * Compute the new desired state from the current state
                //      * Commit the change only if no one else has already changed it (compare-exchange)
                //      * If someone else changed it, try again

            //* Prograss is lock free because if an operation fails to make progress (the compare-exchange
                // returns false) it can only 

        while (current > 0 && !counter.compare_exchange_weak(current, current - 1)) {} // unbounded loop
        return 0;
    }

    bool decrement()
    {
        return counter.fetch_sub(1) == 1;
    }

    uint64_t read() { return counter.load(); }

    std::atomic<uint64_t> counter{ 1 };

    /*
    bool compare_exchange(expected&, desired) {
        if (current_value == expected) {
            current_value = desired; return true;
        else { expected = current_value; return false; }


        }


    }*/

};