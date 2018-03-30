#!/bin/bash
RUNDATE=$(date +%F)
RUNTIME=$(date)
HOMEDIR=/home/eporama
LOGPATH=$HOMEDIR/cronlogs
BACKUPPATH=$HOMEDIR/backups

echo "=================="
echo "Running backup: ${RUNTIME}"

if [ ! -f $LOGPATH ]; then
  echo "creating logpath directory"
  mkdir -p $LOGPATH
fi

if [ ! -d $BACKUPPATH ]; then
  echo "creating backuppath directory"
  mkdir -p $BACKUPPATH
fi

# Create a gzipped sql dump.
echo "running sql-dump"
/var/www/eporama_web/vendor/bin/drush sql-dump --structure-tables-key=common --root=/var/www/eporama_web/web --uri=eporama.com  --gzip --result-file=${BACKUPPATH}/eporama-$(date +%F).sql >> ${LOGPATH}/db-backups.log 2>&1

# Send the backup to S3 for safe keeping
echo "sending backup to s3cmd"
s3cmd --no-progress --no-guess-mime-type put $BACKUPPATH/eporama-${RUNDATE}.sql.gz s3://eporama >> ${LOGPATH}/db-backups.log 2>&1

echo ""
