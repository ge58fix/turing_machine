#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "tm.h"

/* Flag set by ‘--verbose’. */
static int verbose_flag;
char *filename;

int
main (int argc, char **argv)
{
  int c;
  char input[300];

  while (1)
    {
      static struct option long_options[] =
        {
          /* These options set a flag. */
          {"verbose", no_argument,       &verbose_flag, 1},
          {"brief",   no_argument,       &verbose_flag, 0},
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"file",    required_argument, 0, 'f'},
          {"input",   required_argument, 0, 'i'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long (argc, argv, "f:i:",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;

      switch (c)
        {
        case 0:
          /* If this option set a flag, do nothing else now. */
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          break;

        case 'f':
          printf ("option -f with value `%s'\n", optarg);
          filename = optarg;
          break;

        case 'i':
          printf ("option -i with value `%s'\n", optarg);
          snprintf(input, sizeof (input), "%s", optarg);
          break;

        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort ();
        }
    }

  /* Instead of reporting ‘--verbose’
     and ‘--brief’ as they are encountered,
     we report the final status resulting from them. */
  if (verbose_flag)
    puts ("verbose flag is set");

  /* Print any remaining command line arguments (not options). */
  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    }
  Turing_Machine *tm = calloc(1, sizeof(Turing_Machine));
  if(create_tm(filename, tm)) {
      printf("Reading %s failed.\n", filename);
      exit(1);
  }
  if (validate(tm->input_alphabet, input)) {
      printf("Illegal input!\n");
      exit(1);
  }
  printf("tape_alpha: %s\n", tm->tape_alphabet);
  printf("input_alpha: %s\n", tm->input_alphabet);
  printf("current_state: %s\n", tm->current_state);
  exit(0);
}