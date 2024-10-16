class MPZWrapper {
public:
    mpz_t value;
    MPZWrapper() { mpz_init(value); }
    ~MPZWrapper() { mpz_clear(value); }
};