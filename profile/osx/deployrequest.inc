# Creates a deploy-request e-mail for the current branch
deployrequest() {
  if ! (git rev-parse --git-dir > /dev/null 2>&1); then
    echo 'Not a git repo.'
    return 1
  fi
  branch_name=$(git rev-parse --abbrev-ref HEAD)
  commit_log=$(git log --reverse master.. --format='- %s')
  redmine_refs=$(git log master.. --format='%b' | grep refs | sort -u | sed 's/refs #//')
  redmine_urls=$(for ref in $redmine_refs; do echo "https://project.redbet.com/issues/$ref"; done)
  body=$(echo -e "$commit_log\n\n$redmine_urls")
  open "mailto:Redbet IT Support <it-support@redbet.com>?Subject=Deploy request [no special] $branch_name&Body=$body"
}
