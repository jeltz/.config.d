# Creates a deploy-request e-mail for the current branch
deployrequest() {
  if ! (git rev-parse --git-dir > /dev/null 2>&1); then
    echo 'Not a git repo.'
    return 1
  fi
  type -t gnoref > /dev/null && gnoref && return 1
  unset special
  while [ -z "$special" ]; do
    read -p 'Special [y/n]? ' special_answer
    case "$special_answer" in
      [yY]) special='SPECIAL' ;;
      [nN]) special='no special' ;;
      *) echo "'$special_answer' is not an answer." ;;
    esac
  done
  branch_name=$(git rev-parse --abbrev-ref HEAD)
  commit_log=$(git log --reverse master.. --format='%h %s')
  commit_count=$(echo "$commit_log" | wc -l)
  redmine_refs=$(git log master.. --format='%b' | grep refs | sort -u | sed 's/refs #//')
  redmine_urls=''
  unique_refs=0
  for ref in $redmine_refs; do
    redmine_urls+="https://project.redbet.com/issues/$ref\n"
    let unique_refs+=1
  done
  if [ "$special" = 'SPECIAL' ]; then
    deploy_instructions="# Deploy instructions\n1. \n\n"
  else
    deploy_instructions=''
  fi
  body=$(echo -e "# Branch\n$branch_name\n\n$deploy_instructions# Commit$([ $commit_count -gt 1 ] && echo 's')\n$commit_log\n\n# Referenced issue$([ $unique_refs -gt 1 ] && echo 's')\n$redmine_urls" | tr -s '&=?' '_')
  open "mailto:Redbet IT Support <it-support@redbet.com>?Subject=Deploy request [$special] $branch_name&Body=$body"
}