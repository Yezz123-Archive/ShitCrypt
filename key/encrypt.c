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

void loadkey(gcry_sexp_t *kp)
{
    FILE *fp = fopen("./key", "rb");
    if (fp == NULL)
    {
        printf("cannot open the key file.\n");
        exit(1);
    }

    size_t file_len;
    fseek(fp, 0, SEEK_END);
    file_len = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    void *shit_buf = malloc(512 / 8 * 1024);
    if (shit_buf == NULL)
    {
        printf("failed to allocate the space to store the key.\n");
        exit(1);
    }

    fread(shit_buf, 1, file_len, fp);
    fclose(fp);

    size_t error_offset = -1;
    gcry_sexp_sscan(kp, &error_offset, shit_buf, file_len);
    if (error_offset != -1)
    {
        printf("failed to load the key.\n");
        exit(1);
    }
    free(shit_buf);
}

void encrypt(gcry_sexp_t *kp)
{
    gcry_error_t err = 0;
    FILE *fp = fopen("./pt", "rb");
    if (fp == NULL)
    {
        printf("cannot open the plaintext file.\n");
        exit(1);
    }

    size_t file_len;
    fseek(fp, 0, SEEK_END);
    file_len = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *pt_buf = malloc(512 / 8 * 1024);
    if (pt_buf == NULL)
    {
        printf("failed to allocate the space to store the plaintext.\n");
        exit(1);
    }
    memset(pt_buf, 0, 512 / 8 * 1024);
    fread(pt_buf, 1, file_len, fp);
    fclose(fp);

    gcry_mpi_t plaintext = gcry_mpi_new(1024);
    err = gcry_mpi_scan(&plaintext, GCRYMPI_FMT_HEX, pt_buf, 0, NULL);
    if (err)
    {
        printf("failed to parse the plaintext.\n");
        exit(1);
    }

    gcry_sexp_t plaintext_exp;
    err = gcry_sexp_build(&plaintext_exp, NULL,
                          "(data (flags raw) (value %M))", plaintext);
    if (err)
    {
        printf("failed to load the plaintext.\n");
        exit(1);
    }

    gcry_sexp_t ciphertext_exp;
    err = gcry_pk_encrypt(&ciphertext_exp, plaintext_exp, *kp);
    if (err)
    {
        printf("failed to encrypt.\n");
        exit(1);
    }

    gcry_sexp_t shit_a_exp = gcry_sexp_find_token(ciphertext_exp, "a", 1);
    gcry_sexp_t shit_b_exp = gcry_sexp_find_token(ciphertext_exp, "b", 1);

    gcry_mpi_t shit_a = gcry_mpi_new(1024);
    gcry_sexp_extract_param(shit_a_exp, NULL, "a", &shit_a, NULL);

    gcry_mpi_t shit_b = gcry_mpi_new(1024);
    gcry_sexp_extract_param(shit_b_exp, NULL, "b", &shit_b, NULL);

    void *shit_a_str = malloc(512 / 8 * 1024);
    if (shit_a_str == NULL)
    {
        printf("failed to allocate the space to store the ciphertext.\n");
        exit(1);
    }

    void *shit_b_str = malloc(512 / 8 * 1024);
    if (shit_b_str == NULL)
    {
        printf("failed to allocate the space to store the ciphertext.\n");
        exit(1);
    }

    err = gcry_mpi_print(GCRYMPI_FMT_HEX, shit_a_str, 512 / 8 * 1024, NULL, shit_a);
    if (err)
    {
        printf("failed to convert the ciphertext value a.\n");
        exit(1);
    }

    FILE *fp_a = fopen("./ct_a", "wb");
    if (fp_a == NULL)
    {
        printf("failed to store the ciphertext.\n");
        exit(1);
    }
    fprintf(fp_a, "%s\n", (char *)shit_a_str);
    fclose(fp_a);

    err = gcry_mpi_print(GCRYMPI_FMT_HEX, shit_b_str, 512 / 8 * 1024, NULL, shit_b);
    if (err)
    {
        printf("failed to convert the ciphertext value b.\n");
        exit(1);
    }

    FILE *fp_b = fopen("./ct_b", "wb");
    if (fp_b == NULL)
    {
        printf("failed to store the ciphertext.\n");
        exit(1);
    }
    fprintf(fp_b, "%s\n", (char *)shit_b_str);
    fclose(fp_b);
    gcry_mpi_release(plaintext);
    gcry_sexp_release(plaintext_exp);
    gcry_sexp_release(ciphertext_exp);
    gcry_sexp_release(shit_a_exp);
    gcry_sexp_release(shit_b_exp);
    gcry_mpi_release(shit_a);
    gcry_mpi_release(shit_b);
    free(shit_a_str);
    free(shit_b_str);
}

int main()
{
    gcry_error_t err = 0;
    initialize();

    gcry_sexp_t shit_keypair;

    loadkey(&shit_keypair);
    encrypt(&shit_keypair);

    gcry_sexp_release(shit_keypair);

    return 0;
}
