#!/usr/bin/env python
# -*- coding: utf-8 -*-


#Script to get a report of users that commited to a repo every month

import subprocess;
import re;

def main():
    logging.basicConfig(format='%(message)s', level=logging.DEBUG)

    if len(sys.argv) > 1:
        logging.error('Please specify a search dir')
        logging.error('usage: %s <search dir>', sys.argv[0])
        return 1


    for month in range(1, 13):
        logging.debug( "month: %d", month);
        p1 = subprocess.Popen("git shortlog -s -n -e --since='2013-" + `month` + "-01' --until='2013-" + `month` + "-31'", shell=True, stdout=subprocess.PIPE);
        output = p1.communicate()[0];


        f = open('git-authors-' + `month` + '.txt', 'w');
        lines = re.split("\n", output);
        for line in lines:
            matches = re.search(r"\d+\W([\w\W]+) <.*>", line);
            if(matches):
                f.write(matches.group(1) + "\n");



        f.close();

    return 0


if __name__ == '__main__':
    import logging
    import sys

    sys.exit(main())