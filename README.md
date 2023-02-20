# PoreClassify

```
genome_updater.sh \
    -d "refseq"\
    -g "viral" \
    -c "all" \
    -l "all" \
    -f "genomic.fna.gz" \
    -o "refseq-viral" \
    -t 12 \
    -m -a -p

# cd to 2021-09-30_19-35-19

# taxdump
mkdir -p taxdump
tar -zxvf taxdump.tar.gz -C taxdump

cut -f 1,6,20 ../assembly_summary.txt \
| taxonkit lineage -i 2 -r -n -L --data-dir taxdump \
| taxonkit reformat -I 2 -P -t --data-dir taxdump \
| cut -f 1,2,3,4,6,7 > refseq_accessions_taxonomy.csv

```
