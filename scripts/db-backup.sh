#!/bin/bash
RUNDATE=$(date +%F)
RUNTIME=$(date)
HOMEDIR=/home/eporama
WEBDIR=/var/www/eporama_com
LOGPATH=$HOMEDIR/cronlogs
BACKUPPATH=$HOMEDIR/backups
LOG=$LOGPATH/db-backups.log

echo "==================" >> ${LOG} 2>&1
echo "Running backup: ${RUNTIME}" >> ${LOG} 2>&1

if [ ! -d $LOGPATH ]; then
  echo "creating logpath directory" >> ${LOG} 2>&1
  mkdir -p $LOGPATH
fi

if [ ! -d $BACKUPPATH ]; then
  echo "creating backuppath directory" >> ${LOG} 2>&1
  mkdir -p $BACKUPPATH
fi

# Create a gzipped sql dump.
echo "running sql-dump" >> ${LOG} 2>&1
${WEBDIR}}/vendor/bin/drush sql-dump --structure-tables-key=common --root=${WEBDIR}}/web --uri=eporama.com  --gzip --result-file=${BACKUPPATH}/eporama-$(date +%F).sql >> ${LOG} 2>&1

# Send the backup to S3 for safe keeping
echo "sending backup to s3cmd" >> ${LOG} 2>&1
s3cmd --no-progress --no-guess-mime-type put $BACKUPPATH/eporama-${RUNDATE}.sql.gz s3://eporama >> ${LOG} 2>&1

echo "" >> ${LOG} 2>&1
