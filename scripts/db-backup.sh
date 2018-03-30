#!/bin/bash
RUNDATE=$(date +%F)
RUNTIME=$(date)
HOMEDIR=/home/eporama
LOGPATH=$HOMEDIR/cronlogs
BACKUPPATH=$HOMEDIR/backups

echo "==================" >> ${LOGPATH}/db-backups.log 2>&1
echo "Running backup: ${RUNTIME}" >> ${LOGPATH}/db-backups.log 2>&1

if [ ! -f $LOGPATH ]; then
  echo "creating logpath directory" >> ${LOGPATH}/db-backups.log 2>&1
  mkdir -p $LOGPATH
fi

if [ ! -d $BACKUPPATH ]; then
  echo "creating backuppath directory" >> ${LOGPATH}/db-backups.log 2>&1
  mkdir -p $BACKUPPATH
fi

# Create a gzipped sql dump.
echo "running sql-dump" >> ${LOGPATH}/db-backups.log 2>&1
/var/www/eporama_web/vendor/bin/drush sql-dump --structure-tables-key=common --root=/var/www/eporama_web/web --uri=eporama.com  --gzip --result-file=${BACKUPPATH}/eporama-$(date +%F).sql >> ${LOGPATH}/db-backups.log 2>&1

# Send the backup to S3 for safe keeping
echo "sending backup to s3cmd" >> ${LOGPATH}/db-backups.log 2>&1
s3cmd --no-progress --no-guess-mime-type put $BACKUPPATH/eporama-${RUNDATE}.sql.gz s3://eporama >> ${LOGPATH}/db-backups.log 2>&1

echo "" >> ${LOGPATH}/db-backups.log 2>&1
