# Creates a deploy-request e-mail for the current branch
deployrequest() {
  if ! (git rev-parse --git-dir > /dev/null 2>&1); then
    echo 'Not a git repo.'
    return 1
  fi
  open "mailto:Redbet IT Support <it-support@redbet.com>?Subject=Deploy request [no special] $(git rev-parse --abbrev-ref HEAD)&Body=$(git log --reverse master.. --format='- %s')"
}
