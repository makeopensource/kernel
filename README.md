# Project Template Repository

This repository is designed to be a template for how to layout your projects for MakeOpenSource.

## layout

This repo comes with issue templates and a pull request template, as well as this `readme` to use for structuring your projects.

### readme

Using this readme as a template is encouraged to keep consistency, the layout is as follows;

```
# Project Name

a description of the project!
this could be uses, purpose, etc.

## setup

this should be a decently verbose explination in steps of how to recreate the environment that you used to create your project!
it is usually a good idea to start logging how your workflow works pretty quickly after you start the project, that way you don't miss steps.

## licence

this will depend on the project, but all repos should have their applicable licence.
```

## issues

There are templates for each of the different ways a prospective user could interact with your project;

1. a bug
2. a feature request
3. a pull request

This is by no means an exhaustive list, but these have templates for formatting how they should look.

All projects withen MakeOpenSource are open to feedback, so don't feel scared to create a feature request if you want something, or a bug report if you find one, we are all here to learn and encourage feedback!

## git specific stuff

this section is for installing and using git, this is by no means a comprehensive guide, and you should read [this](https://git-scm.com/).

## linux

### cloning a repo

You can clone a repo like so:
`git clone git@github.com:makeopensource/repo-template.git`

Where `git` is the command, `clone` is the argument to the command, and `git@github.com:makeopensource/repo-template.git` is the location of the repo you wish to clone.

When viewing a repo on [github.com](https://github.com), if you are logged in, you should see a green code button at the top right of the repo homepage which gives you the location which to append to your `git clone` command.

### make a commit

After you have edited or created something, and you would like to add it to the repository, you must first add the file:
`git add path/to/file`
Or for adding multiple files: 
`git add file1 file2 file3`

Then you should create a commit message that describes what you changed or created with:
`git commit`

That command will open your default text editor and allow you to write a message, if you only want to add a single line, you can do a message like so:
`git commit -m "stuff that i changed or created"`

After committing your changes, you'll want to `push` your changes;
This step will depend on whether or not you are part of MakeOpenSource or not.

If you are, you'll want to create a branch with your changes;
`git branch -b my-changes`

Then push your changes to the new branch:
`git push origin my-changes`

If you are not in MakeOpenSource, you'll want to fork the repository through github, then set it up as a remote for the cloned repo:
`git remote add my-changes git@github:yourname/repo-template.git`

Then push your changes:
`git push my-changes master`

### pull request

At this stage, you are ready for a pull request!

For both options (a branch or a fork) the steps are almost identical.
On the homepage of the repo, you can go to the `Pull requests` page and click `New pull request`.
If you have already created a branch or forked the repo, and are logged in, github should automagically detect that and prompt you to start the process!

There is a template to follow, which should already be there for you to follow, describing your changes and what they do.
After this, you can submit your pull request and wait for feedback!

## conclusion

This readme will be constantly changing and is very open to feedback and clarification through issues.
