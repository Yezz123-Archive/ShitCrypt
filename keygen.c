#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <include/gpg-error.h>
#include <include/gcrypt.h>
#include <include/gcrypt-module.h>

#define GCRYPT_VERSION "1.4.4"

void initialize()
{
    gcry_error_t err = 0;

    if (!gcry_check_version(GCRYPT_VERSION))
    {
        printf("gcrypt version is mismatched.\n");
        exit(1);
    }
    err |= gcry_control(GCRYCTL_DISABLE_SECMEM, 0);
    err |= gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);

    if (err)
    {
        printf("there is an error in gcrypt initialization.\n");
        exit(1);
    }
}

void keygen(gcry_sexp_t *pp, gcry_sexp_t *kp)
{
    gcry_error_t err = 0;
    err = gcry_sexp_build(pp, NULL, "(genkey (elg (nbits 3:512)))");
    if (err)
    {
        printf("cannot establish the shit key generation.\n");
        exit(1);
    }

    err = gcry_pk_genkey(kp, *pp);
    if (err)
    {
        printf("cannot generate the shit key pair.\n");
        exit(1);
    }
}

void savekey(gcry_sexp_t *kp)
{
    FILE *fp = fopen("./key", "wb");
    if (fp == NULL)
    {
        printf("cannot create the key file.\n");
        exit(1);
    }

    void *shit_buf = malloc(512 / 8 * 1024);
    if (shit_buf == NULL)
    {
        printf("failed to allocate the space to store the key.\n");
        exit(1);
    }

    size_t shit_buf_len;
    shit_buf_len = gcry_sexp_sprint(*kp, GCRYSEXP_FMT_DEFAULT, shit_buf, 512 / 8 * 1024);

    fwrite(shit_buf, 1, shit_buf_len, fp);
    fclose(fp);
    free(shit_buf);
}

void savepp(gcry_sexp_t *kp)
{
    gcry_error_t err = 0;
    gcry_sexp_t shit_p_exp = gcry_sexp_find_token(*kp, "p", 1);
    gcry_sexp_t shit_y_exp = gcry_sexp_find_token(*kp, "y", 1);

    gcry_mpi_t shit_p = gcry_mpi_new(1024);
    gcry_sexp_extract_param(shit_p_exp, NULL, "p", &shit_p, NULL);

    gcry_mpi_t shit_y = gcry_mpi_new(1024);
    gcry_sexp_extract_param(shit_y_exp, NULL, "y", &shit_y, NULL);

    void *shit_p_str = malloc(512 / 8 * 1024);
    if (shit_p_str == NULL)
    {
        printf("failed to allocate the space to store the prime p.\n");
        exit(1);
    }

    err = gcry_mpi_print(GCRYMPI_FMT_HEX, shit_p_str, 512 / 8 * 1024, NULL, shit_p);
    if (err)
    {
        printf("failed to convert the prime p.\n");
        exit(1);
    }
    FILE *fp_p = fopen("./p", "wb");
    if (fp_p == NULL)
    {
        printf("failed to store the prime p.\n");
        exit(1);
    }
    fprintf(fp_p, "%s\n", (char *)shit_p_str);
    fclose(fp_p);

    void *shit_y_str = malloc(512 / 8 * 1024);
    if (shit_y_str == NULL)
    {
        printf("failed to allocate the space to store the public key y.\n");
        exit(1);
    }

    err = gcry_mpi_print(GCRYMPI_FMT_HEX, shit_y_str, 512 / 8 * 1024, NULL, shit_y);
    if (err)
    {
        printf("failed to convert the public key y.\n");
        exit(1);
    }
    FILE *fp_y = fopen("./y", "wb");
    if (fp_y == NULL)
    {
        printf("failed to store the public key y.\n");
        exit(1);
    }
    fprintf(fp_y, "%s\n", (char *)shit_y_str);
    fclose(fp_y);
    gcry_sexp_release(shit_p_exp);
    gcry_sexp_release(shit_y_exp);
    gcry_mpi_release(shit_p);
    gcry_mpi_release(shit_y);
    free(shit_p_str);
    free(shit_y_str);
}

int main()
{
    gcry_error_t err = 0;
    initialize();

    gcry_sexp_t shit_parms;
    gcry_sexp_t shit_keypair;

    keygen(&shit_parms, &shit_keypair);
    savekey(&shit_keypair);
    savepp(&shit_keypair);

    gcry_sexp_release(shit_parms);
    gcry_sexp_release(shit_keypair);

    return 0;
}
