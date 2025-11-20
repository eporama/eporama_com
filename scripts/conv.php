<?php
use League\HTMLToMarkdown\HtmlConverter;

$converter = new HtmlConverter();

$query = \Drupal::entityQuery('node')->condition('type','blog')->accessCheck(FALSE);

$nids = $query->execute();

$nodes = \Drupal\node\Entity\Node::loadMultiple($nids);

foreach ($nodes as $node) { 
    print $node->id() . ': ' . $node->get('body')->format . ': ' . $node->getTitle() . PHP_EOL;
    if ($node->get('body')->format == 'basic_html') {
        print "    Setting to Markdown" . PHP_EOL;
        $node->set('body', [
            'value' => $converter->convert($node->get('body')->value),
            'format' => 'markdown'
        ]);
        $node->save();
    }
    print PHP_EOL;
}
