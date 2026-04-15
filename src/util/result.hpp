#ifndef SINGULARITY_RESULT_HPP
#define SINGULARITY_RESULT_HPP

#include <utility>
#include <string>
#include <stdexcept>

template<typename T, typename E = std::string>
class Result
{
public:
    // Success
    Result(const T& value)
        : _hasValue(true)
    {
        new (&storage.value) T(value);
    }

    Result(T&& value)
        : _hasValue(true)
    {
        new (&storage.value) T(std::move(value));
    }

    // Error
    Result(const E& error)
        : _hasValue(false)
    {
        new (&storage.error) E(error);
    }

    Result(E&& error)
        : _hasValue(false)
    {
        new (&storage.error) E(std::move(error));
    }

    // Copy constructor
    Result(const Result& other)
        : _hasValue(other._hasValue)
    {
        if (_hasValue)
            new (&storage.value) T(other.storage.value);
        else
            new (&storage.error) E(other.storage.error);
    }

    // Move constructor
    Result(Result&& other)
        : _hasValue(other._hasValue)
    {
        if (_hasValue)
            new (&storage.value) T(std::move(other.storage.value));
        else
            new (&storage.error) E(std::move(other.storage.error));
    }

    // Copy assignment
    Result& operator=(const Result& other)
    {
        if (this != &other)
        {
            destroy();
            _hasValue = other._hasValue;

            if (_hasValue)
                new (&storage.value) T(other.storage.value);
            else
                new (&storage.error) E(other.storage.error);
        }
        return *this;
    }

    // Move assignment
    Result& operator=(Result&& other)
    {
        if (this != &other)
        {
            destroy();
            _hasValue = other._hasValue;

            if (_hasValue)
                new (&storage.value) T(std::move(other.storage.value));
            else
                new (&storage.error) E(std::move(other.storage.error));
        }
        return *this;
    }

    ~Result()
    {
        destroy();
    }

    bool hasValue() const
    {
        return _hasValue;
    }

    bool hasError() const
    {
        return !_hasValue;
    }

    explicit operator bool() const
    {
        return _hasValue;
    }

    T& value()
    {
        if (!_hasValue)
            throw std::runtime_error("Result has no value");
        return storage.value;
    }

    const T& value() const
    {
        if (!_hasValue)
            throw std::runtime_error("Result has no value");
        return storage.value;
    }

    E& error()
    {
        if (_hasValue)
            throw std::runtime_error("Result has no error");
        return storage.error;
    }

    const E& error() const
    {
        if (_hasValue)
            throw std::runtime_error("Result has no error");
        return storage.error;
    }

    static Result ok(const T& value)
    {
        return Result(value);
    }

    static Result ok(T&& value)
    {
        return Result(std::move(value));
    }

    static Result fail(const E& error)
    {
        return Result(error);
    }

    static Result fail(E&& error)
    {
        return Result(std::move(error));
    }

private:
    void destroy()
    {
        if (_hasValue)
            storage.value.~T();
        else
            storage.error.~E();
    }

    bool _hasValue;

    union Storage
    {
        T value;
        E error;

        Storage() {}
        ~Storage() {}
    } storage;
};

#endif // SINGULARITY_RESULT_HPP