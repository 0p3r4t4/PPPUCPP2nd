# Git and gitlab.com HowTo

Since I'm a git newbie, I must take notes about useful and basic commands.

## View current branch status

    git status

## Tracking of new files or stage modified files for commit

    git add <file>

## Remove a file from the repository

    git rm <file>

## commit

    git commit -m "Comment"

## push

    git push -u origin master

or, provided that origin is defined and master is the current branch:

    git push

## View git configuration

    git config -l
    git config --local -l
    git config --global -l

## Set the remote URL

    git remote add origin https://gitlab.com/0p3r4t4/PPPUCPP2nd.git

## Change the GitLab remote URL from HTTPS to SSH

    git remote set-url origin git@gitlab.com:0p3r4t4/PPPUCPP2nd.git https://gitlab.com/0p3r4t4/PPPUCPP2nd.git
