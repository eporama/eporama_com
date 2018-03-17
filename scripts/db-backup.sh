#!/bin/bash
HOMEDIR=/home/eporama
LOGPATH=$HOMEDIR/cronlogs
BACKUPPATH=$HOMEDIR/backups

if [ ! -f $LOGPATH ]; then
  mkdir -p $LOGPATH
fi

if [ ! -d $BACKUPPATH ]; then
  mkdir -p $BACKUPPATH
fi

# Create a gzipped sql dump.
/var/www/eporama_web/vendor/bin/drush sql-dump --structure-tables-key=common --root=/var/www/eporama_web/web --uri=eporama.com  --gzip --result-file=${BACKUPPATH}/eporama-$(date +%F).sql >> ${LOGPATH}/db-backups.log 2>&1

# Send the backup to S3 for safe keeping
s3cmd --no-progress --no-guess-mime-type put $BACKUPPATH/eporama-$(date +%F).sql.gz s3://eporama >> ${LOGPATH}/db-backups.log 2>&1
