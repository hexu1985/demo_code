"use strict";(self.webpackChunkheifetz=self.webpackChunkheifetz||[]).push([[620],{27072:function(e,n,t){var o=t(8672),i=t(21620),a=t(61869),r=t(84421),s=t(88483),d=t(16600),l=t(78194),c=t(61565),u=t(32554),h=t(68562),p=t(87363),m=t(74792),w=t(71113),f=t(43819),v=t(17341),A=t(90041),g=t(61963),C=t(78209),S=t(47112),Z=t.n(S),b=t(40491),y=t.n(b),k=t(75926),I=t.n(k),x=t(30063),E=t(58301),R=t(3404),M=t(38359),B=t(65406),T=t(17222),P=t(48457),N=t(86536),z=t(8412),O=t(39849),V=t(49236),D=t(36701),_=t(714),q=t(96323),L=t(97645),U=t.n(L),H=t(62702),F=t(76224),W=t(64937),G=t(73464),Q=t(60048),X=t(44707),K=t(89237),j=t(63328),$=t(20722),J=t(73587),Y=t(59039),ee=t(20829),ne=t(70175),te=t(91355),oe=t(440),ie=t(14468),ae=t(43158),re=t(67694),se=t(87655),de=t(27869),le=t(38174),ce=t(2790),ue=t(49),he=t(40198),pe=t(92799),me=t(24316),we=t(29254),fe=t(64833),ve=t(50647),Ae=t(64448),ge=t(95331),Ce=t(45638),Se=t(30942),Ze=t(5671),be=t(67184),ye=t(35803),ke=t(50029),Ie=t(74264),xe=t(70880),Ee=t(25949),Re=t(46434),Me=t(51866),Be=t(70538),Te=t(81525),Pe=t(8905),Ne=t(33156),ze=t(4244),Oe=t(5700),Ve=t(34614),De=t(23e3),_e=t(38899),qe=t(21372),Le=t(68324),Ue=t(23993),He=t(49248),Fe=t(43251),We=t(6121),Ge=t(41191),Qe=t(29713),Xe=t(73804),Ke=t(56765),je=t(1526),$e=t(91449),Je=t(51587),Ye=t(15667),en=t(60357),nn=function(e){return"plain"===e||"special-plain"===e},tn=nn,on=function(e){return"special-plain"===e},an={allowed:"允许规范转载",need_payment:"允许付费转载",disallowed:"禁止转载"},rn=function(e){var n;if(e.videoAnswerData)return e;if(null===(n=e.attachment)||void 0===n?void 0:n.video){var t=e.attachment.video,o=t.title,i=t.subVideoId,a=t.parentVideoId,r=t.zvideoId,l={videoId:i,zvideoId:r,title:o,playCount:t.playCount,voteupCount:t.voteupCount,isComplete:!r||a===i,startTime:t.startTime,creationReferences:t.creationReferences};return(0,d.Z)((0,s.Z)({},e),{videoAnswerData:l})}return e};function sn(e){var n=(0,ie.AU)(e);return n?e.videoAnswerData&&"object"==typeof e.videoAnswerData?(0,d.Z)((0,s.Z)({},e),{creationRelationship:n,videoAnswerData:(0,d.Z)((0,s.Z)({},e.videoAnswerData),{creationRelationship:n})}):(0,d.Z)((0,s.Z)({},e),{creationRelationship:n}):e}var dn=["zhi-hu-ri-bao-51-41"],ln=(0,B.P1)((function(e,n){return(0,d.Z)((0,s.Z)({},n.answerFromProps?n.answer:e.entities.answers[n.answer.id]||n.answer),{videoAnswerData:n.answer.videoAnswerData})}),(function(e,n){return e.entities.questions[n.answer.question.id]}),(function(e,n){return n?(0,d.Z)((0,s.Z)({},e),{question:(0,s.Z)({},e.question,n)}):e})),cn=function(e){(0,r.Z)(t,e);var n=(0,u.Z)(t);function t(){var e,a,r,l,u,m,w,f;return(0,i.Z)(this,t),(e=n.apply(this,arguments)).state={commentsShown:!1,commentsAutoFocus:!0,reportModalShown:!1,deleteModalShown:!1,collapseModalShown:!1,favlistsShown:!1,editing:!1,commentPattern:"fixed",addAnnotationModalShown:!1,cancelAnnotationModalShown:!1,guideShown:!1,shareVideoQuery:e.getShareVideoId(),shouldShowVideoDetails:!1,contentExpanded:e.props.expanded,hasFetchedLabels:!1,showWechatExpand:!1,skipModalShow:!1,autoExpand:!1,shownLoadingBar:!1,wxIsReady:!1},e.answerFormRef=(0,p.createRef)(),e.rewardContainerRef=(0,p.createRef)(),e.richContentRef=(0,p.createRef)(),e.zaRef=(0,p.createRef)(),e.loadEntityWords=y()((function(){var n=e.props,t=n.answer,o=(void 0===t?{}:t).id;(0,n.loadAnswerEntityWords)(o)})),e.handleLoadedNext=function(){e.setState({wxIsReady:!0}),e.state.shownLoadingBar&&e.createOpenInAppHandler(e.state.autoExpand?"expand_answer2":"expand_answer1")(),e.setState({shownLoadingBar:!1})},e.showOiaModal=function(){var n=e.props,t=n.blockReading,o=n.itemProp,i=n.isBaidu;("mainEntityOfPage"===o||"acceptedAnswer"===o)&&!i&&!document.referrer.includes("sm.cn")&&t&&e.setState({showWechatExpand:!0,autoExpand:!0})},e.onCloseReward=function(){var n=e.props.answer.id;U().set("isRewardable",!1),e.props.updateAnswerReward(n,"")},e.openModal=function(n,t){e.setState((0,s.Z)({},t)),t.commentsShown?e.props.trackOpenCommentAdPromotion():e.props.trackCloseCommentAdPromotion()},e.openDeleteModal=function(){setTimeout((function(){e.setState({deleteModalShown:!0})}))},e.closeModal=function(){e.setState({commentsShown:!1});var n=e.props.onCloseComment;"function"==typeof n&&n(),e.props.trackOpenCommentAdPromotion()},e.closeDeleteModal=function(){e.setState({deleteModalShown:!1})},e.disableAuth=(a=e.props,r=a.router,l=(void 0===r?{}:r).location,u=(void 0===l?{}:l).pathname,m=a.isBaidu,w=a.isMobile,f=a.currentUser,w&&!f&&!m&&!u.startsWith("/topic")),e.loadAnswerConcernedVoters=function(){var n=e.props,t=n.concernedUpvoters,o=n.answer,i=n.loadAnswerConcernedVoters,a=n.currentUser;!t&&a&&i(o.id)},e.handleExpand=function(n){var t=arguments.length>1&&void 0!==arguments[1]?arguments[1]:{},o=t.trackUserAction,i=void 0===o||o,a=e.props,r=a.onToggleExpand,s=a.trackPromotionClick;r&&r(n),n&&e.loadAnswerConcernedVoters(),i&&n&&s&&s(),e.setState({contentExpanded:n})},e.handleReshipmentSettings=function(n){var t=e.props,o=t.answer.id,i=t.updateAnswerReshipmentSettings,a=t.fillCurrentUserIfNeeded;"need_payment"===n?Promise.resolve(a(["caEnabled"])).then((function(){e.props.currentUser.caEnabled?i(o,n):window.open("/copyright/invite")})):i(o,n)},e.handleLoadAnswerForSettings=function(){var n=e.props,t=n.answer.id;(0,n.loadAnswerForSettings)(t)},e.handleDeleteAnswer=function(){var n=e.props,t=n.answer.id;(0,n.deleteAnswer)(t)},e.handlePositionStatusChange=function(n){e.setState({positionStatus:n})},e.handleCollapseModalShow=function(){e.setState({collapseModalShown:!0})},e.handleCollapseModalHide=function(){e.setState({collapseModalShown:!1})},e.handleUpdateAnswerCollapsed=function(){var n=e.props,t=n.answer,o=t.id,i=t.collapsedBy,a=n.updateAnswerCollapsed,r=n.showNotification;return"community"===i?r("该回答因违反社区规范已被管理员折叠，暂无法公开","red"):a(o)},e.handleUpdateAnswerStick=function(){var n=e.props,t=n.answer.id;return(0,n.updateAnswerStick)(t)},e.handleRestoreAnswer=function(){var n=e.props,t=n.answer,o=t.id,i=t.question;(0,n.restoreAnswer)(i.id,o)},e.handleClickCommentsPreview=function(n){var t=e.props,o=t.isMobile,i=t.relatedTo;o&&"answer"===i&&(n.stopPropagation(),e.setState({commentsShown:!0}))},e.openInApp=function(){(0,J.Z)({trackEvent:e.zaRef.current.trackEvent,zaV3Text:"评论弹层",noEnteringSignin:Boolean(e.props.currentUser)})},e.setEditingState=function(n,t){"function"==typeof e.props.onEditingStateChange&&e.props.onEditingStateChange(n),e.setState({editing:n},t)},e.handleStartEditAnswer=function(){var n=e.props,t=n.draftStatus,o=n.hasPublishingDraft,i=n.isMobile,a=n.isAnswerPage,r=n.showNotification,s=n.answer,d=s.author,l=s.id,c=s.question.id,u=s.question,h=(0,W.i)(u);(0,W.S)(d)&&""!==h?r(h,"red"):t&&t.loading?D.Z.alert("草稿正在加载中……"):o?D.Z.alert("你有一份对该回答的修改正在发布中，请等待发布完成后再次修改。"):i?e.context.startAddAnswer(e.props.answer.id):a?(0,F.$$)()?(0,F.aH)(c,l):e.setEditingState(!0,(function(){var n,t;null===(n=e.answerFormRef.current)||void 0===n||null===(t=n.focus)||void 0===t||t.call(n)})):(0,F.aH)(c,l)},e.handleCancelEditAnswer=function(){e.setEditingState(!1);var n=e.props,t=n.onCloseEditing,o=n.onCloseComment;"function"==typeof o&&o(),"function"==typeof t&&t()},e.handleSubmitAnswer=function(n){var t=e.props,o=t.answer.id,i=t.updateAnswer;return e.handleCancelEditAnswer(),i(o,n).then((function(n){return T.Z.trackEvent(e.contentItem,{action:"StatusReport"},{status:{result:"Success",event:{action:"Edit"}}}),n}))},e.handleReportOpen=function(){var n=e.props.zaInfos.report;T.Z.trackEvent(e.contentItem,(0,s.Z)({action:"Report",element:"Button",is_intent:!0},n&&{id:n})),e.props.authRequired((function(){return e.setState({reportModalShown:!0})}),te.q0.report)()},e.handleReportHide=function(){e.setState({reportModalShown:!1})},e.handleFavlistsShown=function(n){var t=e.props,o=t.shouldOia,i=t.zaInfos.favlists;T.Z.trackEvent(e.favButtonRef,(0,s.Z)({action:"Collect",element:"Button",is_intent:!0},i&&{id:i})),o?e.createOpenInAppHandler("collect_answer")(n):e.disableAuth?e.handleToggleGuide():e.props.authRequired((function(){return e.setState({favlistsShown:!0})}),te.q0.favlists)()},e.handleFavlistHide=function(){e.setState({favlistsShown:!1})},e.handleLogMoreClick=function(){var n=e.props.zaInfos.options;T.Z.trackEvent(e.contentItem,(0,s.Z)({action:"Click",element_name:"MoreAction"},n&&{id:n}))},e.handleShowAddAnnotationModal=function(){return e.setState({addAnnotationModalShown:!0})},e.handleCloseAddAnnotationModal=function(){return e.setState({addAnnotationModalShown:!1})},e.handleShowCancelAnnotationModal=function(){return e.setState({cancelAnnotationModalShown:!0})},e.handleCloseCancelAnnotationModal=function(){return e.setState({cancelAnnotationModalShown:!1})},e.handleToggleGuide=function(){e.setState({guideShown:!e.state.guideShown})},e.handleClickVideoMoreButton=function(){e.setState({shouldShowVideoDetails:!1})},e.handleClickTitle=function(n){var t=e.props,o=t.onClickTitle,i=t.trackPromotionClick,a=t.answer.id;n.preventDefault(),null==o||o(a),window.open(e.href),null==i||i()},e.startEditing=function(){var n=e.props,t=n.isAuthor,o=n.editable;n.currentUser&&t&&o&&e.handleStartEditAnswer()},e.addRewardTagline=function(n){var t=e.props.answer.id;(0,fe.OC)(n,t)},e.createOpenInAppHandler=function(n){var t=arguments.length>1&&void 0!==arguments[1]&&arguments[1],i=e.props,a=i.answer,r=a.type,l=a.id,c=i.blockReading,u=i.isSpecialQuestionOrAnswer,h=i.currentUser,p=i.relatedTo;return function(i,a){if(i&&i.preventDefault(),"answer"===p)if(c&&T.Z.trackEvent((0,o.Z)(e),{id:5550,action:"Click"},{button:{text:"openapp"}}),u)location.href="zhihu://".concat(r,"/").concat(l,"?utm_app_name=zhihu_check");else{var m=te.t6[a]||te.t6[n],w=(0,d.Z)((0,s.Z)({},c&&{yyb_ckey:"CK1430255776739"}),{preventToOIA:t});te.dN[m]&&(w.launch_button=te.dN[m]);var f=te.ov[a]||te.ov[n];(0,J.Z)({trackEvent:e.zaRef.current.trackEvent,zaV3Text:f,noEnteringSignin:Boolean(h)},w)}}},e.renderLabels=function(){var n=e.props.answer,t=n.isNormal;if((void 0===t||t)&&e.isPaidAnswer)return{labels:[],editingLabels:[]};var o=e.props,i=o.useNewLabels,a=o.canCollapse,r=o.relatedTo,l=o.showReviewingLabel,c=o.hideCommercialInviteLabel,u=e.state,p=u.contentExpanded,m=u.editing,w=(0,je.gh)({answer:n,canCollapse:a,showReviewingLabel:l}),f=(0,je.xx)(n),v=(0,je.Dm)({answer:n,canCollapse:a,hideCommercialInviteLabel:c}),A=(0,je.fb)(n);if(!i){var g=(0,h.tZ)(De.Z,(0,d.Z)((0,s.Z)({useOldLabels:!0,item:{isLabeled:!0}},f),{commercialProps:v,annotationProps:A,showLegacyPositiveLabel:(0,de.G_)(n),editing:m}));return{labels:[w,g],editingLabels:[g]}}if(w||f)return{labels:[w,(0,h.tZ)(De.Z,(0,s.Z)({item:{isLabeled:!0}},f),"labels")],editingLabels:[]};var C=[(0,h.tZ)(De.Z,{item:n,commercialProps:v,annotationProps:A,editing:m},"labels")];return{labels:p||r?C:[],editingLabels:C}},e.renderPrefix=function(){var n=e.props,t=n.answer,o=n.relatedTo,i={contentExpanded:e.state.contentExpanded,unescapable:Boolean(o)};return e.isVideoAnswer&&!e.contentDisplayed&&e.coCreate?(0,h.tZ)(X.xJ,{mb:"4px"}):(0,Je.Z)(t,i)},e.renderVoteButton=function(){var n=e.props,t=n.answer,o=n.shouldOia,i=n.zaInfos,a=i.voteUp,r=i.voteDown,l=n.isMuteSpecial,c=n.isMuteFreeze,u=n.isAuthor,p=n.currentUser,m=e.state.positionStatus,w=t.question,f=w.questionType,v=w.isMuted,A=t.relationship,g=void 0===A?{}:A,C=g.isRecognized,S=g.voting,Z=t.attachment,b=t.voteupCount,y="commercial"===f&&v||l||c;return e.isLegacyVideoAnswer?(0,h.tZ)(en.Z,{answer:t,id:Z.attachmentId,voteupCount:b,voting:S,isOwner:u,disabled:y,currentUser:p}):(0,h.tZ)(Ke.Z,(0,d.Z)((0,s.Z)({answer:t,disabled:y,isOwner:u},o&&{onClick:e.createOpenInAppHandler("vote_answer")}),{disableAuth:e.disableAuth,isRecognized:C,handleToggleGuide:e.handleToggleGuide,positionStatus:m,zaIds:{voteUp:a,voteDown:r}}),"vote")},e.renderAuthorInfo=function(){var n=e.props,t=n.preset,o=n.relatedTo,i=n.answer,a=i.id,r=i.author,s=i.creationRelationship,d=n.trackToggleFollowAdPromotion;if(e.coCreate){var l=!on(t);return(0,X.SF)(t,r,s,l)}return!on(t)&&(0,h.tZ)(Ie.Z,{className:Z()("AnswerItem-authorInfo",{"AnswerItem-authorInfo--related":o}),preset:tn(t)?"plain":"default",author:r,relatedTo:o,id:a,userLinkV2:!0,onToggleFollow:d},"authorInfo")},e.renderMetaAndBeforeContent=function(){var n,t,o=e.props,i=o.preset,a=o.answer.creationRelationship,r=e.renderAuthorInfo(),s=e.renderAnswerExtraInfo(),d=e.renderLabels().labels,l=null==a||null===(n=a.coCreation)||void 0===n?void 0:n.refBy,u=null==a||null===(t=a.reference)||void 0===t?void 0:t.refBy,p=e.contentDisplayed&&(l||u)&&(0,h.tZ)(R.Box,{my:"16px",children:(0,h.tZ)(X.j7,{type:"answer",coCreationRefBy:l,referenceRefBy:u})});return nn(i)?[[r].concat((0,c.Z)(d),[p]),s]:[[r].concat((0,c.Z)(d),[p,s]),null]},e}var m=t.prototype;return m.componentDidMount=function(){var e=this,n=this.props,t=n.expanded,o=n.byComment,i=n.editing,a=n.loadVideoDetails,r=n.isSearchSpecialSource,s=n.isMobile,d=n.isWechat,l=this.state.shareVideoQuery;if(l&&a(l).then((function(){e.setState({shouldShowVideoDetails:!0})})),t&&(this.loadAnswerConcernedVoters(),this.loadEntityWords()),o&&setTimeout((function(){return e.setState({commentsShown:Boolean(o)})})),i&&this.startEditing(),s&&!r&&this.showOiaModal(),s&&d)if(document.addEventListener("WeixinJSBridgeReady",(function(){e.handleLoadedNext()})),"complete"===document.readyState)this.handleLoadedNext();else{var c=function(){window.removeEventListener("load",c),e.handleLoadedNext()};window.addEventListener("load",c)}},m.componentDidUpdate=function(e,n){!n.contentExpanded&&this.state.contentExpanded&&this.loadEntityWords(),!this.props.editing||e.editing||this.state.editing||this.startEditing()},m.UNSAFE_componentWillReceiveProps=function(e){var n=this,t=this.props.answer,o=t.reshipmentSettings,i=t.commentPermission,a=e.answer,r=a.reshipmentSettings,s=a.commentPermission;!o&&r&&!i&&s&&setTimeout((function(){return n.settingsTogglerEl.click()}))},m.getShareVideoId=function(){var e=this.props,n=e.location;return e.isMobile?n.query.preview_video_id:null},m.renderReshipmentSettings=function(e){var n=this,t=this.props.currentUser;return Object.keys(an).map((function(o){return"need_payment"===o&&(null==t?void 0:t.isOrg)?null:(0,h.tZ)(Ae.Z,{onClick:function(){return n.handleReshipmentSettings(o)},checked:o===e,children:an[o]},o)}))},m.renderAnswerExtraInfo=function(){var e=this.props,n=e.answer,t=e.actor,o=e.action,i=e.concernedUpvoters,a=e.isHuman,r=e.useNewLabels,s=e.isMobile,d=n.id,l=n.voteupCount,c=n.markInfos,u=n.isNormal;if(!((!a||!s)&&(void 0===u||u)))return null;var p=(null==c?void 0:c.length)>0&&!r;return p||l?(0,h.tZ)(Qe.Z,{id:d,voteupCount:l,markInfos:p&&c,actorToken:null==t?void 0:t.urlToken,action:o,concernedUpvoters:i},"AnswerItemExtraInfo"):null},m.renderSettings=function(){var e=this,n=this.props,t=n.answer,o=t.id,i=t.collapsedBy,a=t.reshipmentSettings,r=t.commentPermission,s=t.question.questionType,d=t.rewardInfo,l=(void 0===d?{}:d).isRewardable,c=void 0!==l&&l,u=t.relevantInfo,p=t.creationRelationship,m=n.answer,w=n.canCollapse,v=n.isMobile;if(!n.currentUser||!this.isAuthorInGeneral)return null;var A=(0,h.BX)(h.HY,{children:[this.renderReshipmentSettings(a),(0,h.tZ)(q.R,{}),(0,h.tZ)(oe.rt,{className:"AnswerItem-selectMenuItem",target:m,onChange:this.props.updateAnswerCommentPermission,current:r}),(0,h.tZ)(q.R,{}),c&&(0,h.tZ)(q.sN,{onClick:this.onCloseReward,children:"关闭赞赏"}),(0,h.tZ)(q.sN,{onClick:this.openDeleteModal,children:"删除"}),"commercial"===s&&w&&"nobody"===i&&(!u||"brand_special"!==u.relevantType)&&[(0,h.tZ)(q.R,{},"MenuDivider"),(0,h.tZ)(q.sN,{onClick:this.handleUpdateAnswerCollapsed,children:"隐藏"},"MenuItem")]]});if(a&&r){var g,C,S=null==p||null===(g=p.coCreation)||void 0===g||null===(C=g.bizInfo)||void 0===C?void 0:C.canCancelPermission;return(0,h.tZ)(q.ZP,{arrowed:Boolean(S),toggler:(0,h.tZ)(G.ZP,{preset:"plain",onRef:function(n){e.settingsTogglerEl=n},icon:f.T,label:!v&&"设置"}),reversed:!0,menuClassName:"AnswerItem-selfMenu",itemClassName:"AnswerItem-selectMenuItem",children:S?(0,h.tZ)(q.sN,{children:(0,h.tZ)(X.ZY,{contentType:"answer",contentId:o})}):A},"settings")}return(0,h.tZ)(G.ZP,{preset:"plain",onClick:this.handleLoadAnswerForSettings,icon:f.T,label:!v&&"设置"},"settings")},m.renderReshipment=function(e,n){var t=this;return"need_payment"===n?(0,h.tZ)(q.sN,{onClick:function(){T.Z.trackEvent(t.contentItem,{action:"Authorize",element:"Button",is_intent:!0})},tag:"a",href:"/copyright/apply?answer=".concat(e),target:"_blank",children:"申请授权"}):"disallowed"===n?(0,h.tZ)(q.sN,{tag:"a",target:"_blank",href:"/term/zhihu-terms#sec-licence-6",children:"禁止转载"}):null},m.renderOptions=function(){var e=this;if(!this.props.currentUser||this.isAuthorInGeneral)return null;var n=this.props,t=n.answer,o=n.canCollapse,i=n.renderExtraOptions,a=n.permission.canBrandAdminEdit,r=n.isMobile,l=n.isAuthor,c=t.id,u=t.reshipmentSettings,m=t.collapsedBy,w=t.question,f=w.questionType,A=w.brand,g=(void 0===A?{}:A).isPuQuestion,C=t.annotationAction,S=void 0===C?[]:C,Z=t.annotationDetail,b={toggler:(0,h.tZ)(G.ZP,{preset:"plain",className:"OptionsButton",icon:v.AZ,"aria-label":"更多"}),reversed:!0,onOpen:this.handleLogMoreClick,menuClassName:"AnswerItem-selfMenu",itemClassName:"AnswerItem-selfMenuItem"},y="commercial"===f,k="nobody"!==m;return l?null:(0,p.createElement)(q.ZP,(0,d.Z)((0,s.Z)({},b),{key:"options",children:[r&&(0,h.tZ)(Ce.HS,{answer:t}),o&&!y&&(0,h.tZ)(q.sN,{onClick:k?this.handleUpdateAnswerCollapsed:this.handleCollapseModalShow,children:k?"取消隐藏":"隐藏"}),a&&y&&!k&&!g&&(0,h.tZ)(q.sN,{onClick:this.handleUpdateAnswerCollapsed,children:"隐藏"}),S&&S.some((function(e){return te.jB.add===e}))&&!Z&&(0,h.tZ)(q.sN,{onClick:this.handleShowAddAnnotationModal,children:"标记内容"}),S&&S.some((function(e){return te.jB.cancel===e}))&&Z&&(0,h.tZ)(q.sN,{onClick:this.handleShowCancelAnnotationModal,children:"撤销标记"}),(0,h.tZ)(P.$U,{zaAction:"Report",zaType:"Button",zaModuleId:"click_report",as:q.sN,onClick:this.handleReportOpen,children:"举报"}),this.renderReshipment(c,u),i&&i({itemClassName:"AnswerItem-selfMenuItem",getContainer:function(){return e.contentItem}})]}))},m.renderMeta=function(){var e=function(e){var n=e.thumbnail,t=e.voteupCount,o=e.question.id,i=e.id,a=e.createdTime,r=e.updatedTime,s=e.commentCount;return{image:n,upvoteCount:t,url:"https://www.zhihu.com/question/".concat(o,"/answer/").concat(i),dateCreated:new Date(1e3*a).toISOString(),dateModified:new Date(1e3*r).toISOString(),commentCount:s}}(this.props.answer);return Object.keys(e).map((function(n){return(0,h.tZ)("meta",{itemProp:n,content:e[n]},n)}))},m.renderBrandQuestionPrizeTip=function(){var e=this.props.answer,n=e.id,t=e.question.prize,o=void 0===t?{}:t,i=o.winnersAnswerTokens,a=o.prizes;if(!o.status)return null;var r=["一","二","三"],s=null;return a&&i&&i.forEach((function(e,t){e.includes(n)&&null===s&&(s=a&&a[1]&&a[1].name?"得".concat(r[t],"等奖"):"奖")})),s&&(0,h.BX)("div",{className:"AnswerItem-brandQuestionPrizeTip",children:["该回答在有奖问答中获",s]})},m.renderBrandEntityTrack=function(){var e=this.state.contentExpanded,n=this.props,t=n.answer,o=n.expanded,i=n.isBrandAnswer,a=t.question;return(o||e)&&(a&&"commercial"===a.questionType||i)?(0,h.tZ)(xe.Z,{type:t.type,id:t.id}):null},m.renderEditTime=function(){var e,n,t,o=this.props,i=o.shouldOia,a=o.answer,r=a.createdTime,l=a.updatedTime,c=a.playCount,u=a.attachment,p=a.ipInfo,m=c||(null==u||null===(e=u.zvideo)||void 0===e?void 0:e.playCount)||(null==u||null===(n=u.video)||void 0===n||null===(t=n.videoInfo)||void 0===t?void 0:t.playCount)||0;return(0,h.tZ)(We.O,(0,d.Z)((0,s.Z)({created:r,updated:l,href:this.href},this.isVideoAnswer&&m>0&&{videoPlayCount:Number(m)},i&&{onClick:this.createOpenInAppHandler("click_answer")}),{ipInfo:p}))},m.render=function(){var e,n,t,o=this,i=this.props,a=i.answer,r=i.reward,c=i.answer,u=c.id,p=c.isNormal,m=void 0===p||p,f=c.isDelete,v=c.question,S=c.rewardInfo,b=void 0===S?{}:S,y=c.question,k=y.title,I=y.id,x=y.questionType,E=y.commercial,M=y.brand,B=(void 0===M?{}:M).isPuQuestion,T=c.author,O=c.excerpt,V=c.content,q=c.editableContent,L=c.commentCount,U=c.adminClosedComment,F=c.collapsedBy,W=c.isSticky,X=c.thumbnail,K=c.thumbnailExtraInfo,J=c.reviewInfo,ne=void 0===J?{}:J,oe=ne.isReviewing,ie=ne.editType,se=c.relevantInfo,de=(void 0===se?{}:se).relevantType,le=c.annotationDetail,ce=c.paidInfo,ue=void 0===ce?{}:ce,he=c.creatorRightsNotification,pe=c.attachment,me=c.videoAnswerData,we=i.relatedTo,fe=i.editable,ve=i.byComment,Ae=i.draft,ge=i.expanded,Ze=i.lastreadTouchable,Ie=i.canCollapse,xe=i.canStick,Ve=i.itemProp,De=void 0===Ve?"answer":Ve,Qe=i.addAnnotation,Ke=i.cancelAnnotation,je=i.showNotification,Je=i.dataZaIndex,en=i.blockReading,nn=i.isWechat,tn=i.isHuaweiBrowser,on=i.isHonor,an=i.lessExcerpt,rn=i.isHuman,sn=i.ua,dn=i.shouldSpecialOia,ln=i.shareVideoDetail,cn=i.formatContent,un=i.zaInfos,hn=un.expand,pn=un.title,mn=un.thank,wn=un.toggleComment,fn=un.share,vn=un.getCommentAction,An=i.handleToggleSticky,gn=i.renderActionButtons,Cn=i.permission.canBrandAdminEdit,Sn=i.readContentRightsNotification,Zn=i.ecommerce,bn=i.isMobile,yn=i.canAbstract,kn=i.isBaidu,In=i.isMuteSpecial,xn=i.isMuteFreeze,En=i.isAuthor,Rn=i.shouldHidePaidIntroWhenCollapsed,Mn=i.xiaomi,Bn=i.showCommentForOia,Tn=i.pathname,Pn=i.richContentKey,Nn=i.shouldAlwaysShowPlayer,zn=i.isShenma,On=i.isRecommend,Vn=i.videoRef,Dn=i.alwaysShowVolumeButton,_n=i.showHeightLight,qn=void 0!==_n&&_n,Ln=i.truncateDisabled,Un=void 0!==Ln&&Ln,Hn=i.forceCommentOia,Fn=void 0!==Hn&&Hn,Wn=i.hideCoCreationFeature,Gn=i.entityWords,Qn=i.isAnswerPage,Xn=i.currentUser,Kn=i.blockStrategies,jn=i.trackShareAdPromotion,$n=i.trackPublishCommentAdPromotion,Jn=(0,Se.Z)([(0,Se.m)(Kn)],gn),Yn="function"==typeof An,et=this.state,nt=et.reportModalShown,tt=et.deleteModalShown,ot=et.collapseModalShown,it=et.favlistsShown,at=et.editing,rt=et.commentsShown,st=et.commentsAutoFocus,dt=et.commentPattern,lt=et.addAnnotationModalShown,ct=et.cancelAnnotationModalShown,ut=et.positionStatus,ht=et.shareVideoQuery,pt=et.shouldShowVideoDetails,mt=et.contentExpanded,wt=et.showWechatExpand,ft=et.skipModalShow,vt=et.autoExpand,At=et.shownLoadingBar,gt=et.wxIsReady,Ct=null==pe||null===(e=pe.video)||void 0===e?void 0:e.campaign,St=ht&&pt?{title:ln.title,thumbnail:ln.coverUrl,isLens:!0,id:ht,isPlayable:!0,url:"https://www.zhihu.com/video/".concat(ht)}:null;if(f)return(0,h.BX)("div",{className:"AnswerItem-deleted",children:["你已经删除了该问题的回答，如果需要修改，请先  ",(0,h.tZ)("a",{role:"button",tabIndex:0,onClick:this.handleRestoreAnswer,children:"撤销删除"})]});var Zt=!this.isVideoAnswer||!(oe&&"create"===ie),bt="commercial"===x,yt="nobody"!==F,kt=X||(null==pe||null===(n=pe.video)||void 0===n||null===(t=n.videoInfo)||void 0===t?void 0:t.thumbnail);if(at){var It,xt=ye.Z,Et=(0,h.BX)("div",{children:[(0,h.BX)(R.Flex,{alignItems:"center",justifyContent:"space-between",css:function(e){return[{borderBottom:"1px solid ".concat(e.colors.GBK09A),".Tabs":{border:"none"}},{background:e.colors.GBK99A}]},children:[(0,h.tZ)("div",{css:function(e){return[{fontWeight:"bold",fontSize:15,color:e.colors.GBK03A,borderBottom:"1px solid ".concat(e.colors.GBK10A)},{borderBottom:"none",paddingLeft:20}]},children:this.isVideoAnswer?"本回答为视频回答":"本回答为图文回答"}),(0,h.tZ)(ke.Z,{handleClick:null===(It=this.answerFormRef.current)||void 0===It?void 0:It.toggleFullscreen})]}),(0,h.tZ)(xt,{className:"AnswerItem-form",isReediting:!0,imperativeRef:this.answerFormRef,question:v,answer:a,defaultValue:q,onDeleteDraft:this.handleCancelEditAnswer,onCancel:this.handleCancelEditAnswer,onSubmit:this.handleSubmitAnswer,isRewardable:b.isRewardable,addRewardTagline:this.addRewardTagline,useMediumEditor:!0})]});return Qn?(0,h.tZ)(H.Z,{children:(0,h.tZ)(_.ZP,{css:{overflow:"visible"},children:(0,h.BX)("div",{css:function(e){return{background:e.colorMod(e.colors.GBK10C).alpha(.45)}},children:[(0,h.tZ)(Y.Z,{}),Et]})})}):Et}var Rt=(0,l.Z)(this.renderMetaAndBeforeContent(),2),Mt=Rt[0],Bt=Rt[1],Tt="mainEntityOfPage"===De||"acceptedAnswer"===De,Pt=dn&&!Tt,Nt=!St&&this.renderEditTime(),zt=ue.type,Ot=ue.content,Vt=this.isPaidAnswer,Dt=Vt?Ot:V,_t=!we&&(0,h.tZ)($e.Z,{questionId:I,title:k,href:this.href,zaTitleId:pn,showStickyMark:Yn&&this.props.isSticky,showHeightLight:qn,onClick:this.handleClickTitle}),qt=m||En,Lt=Mn&&Tn.match(/\/question\/\d+$/g),Ut=cn?cn(Dt||O,a):Dt||O||"",Ht=me&&(Nn||this.contentDisplayed),Ft=On&&this.isVideoAnswer,Wt=bn&&"answer"===we;return(0,h.BX)(Pe.ZP,{onRef:function(e){return o.contentItem=e},className:"AnswerItem","data-za-index":Je,"data-zop":JSON.stringify({authorName:null==T?void 0:T.name,itemId:u,title:k,type:"answer"}),data:a,link:this.href,meta:Ft?null:Mt,title:_t,lastreadTouchable:Ze,name:u,itemProp:De,itemType:"http://schema.org/Answer",itemScope:!0,children:[m&&(!Rn||mt)&&(0,h.tZ)(Xe.m,{answer:a}),this.renderMeta(),bt&&this.renderBrandQuestionPrizeTip(),this.renderBrandEntityTrack(),qt?(0,h.BX)(h.HY,{children:[this.isVideoAnswer&&(0,h.tZ)(w.eb,{data:K,children:(0,h.tZ)(Ye.Z,(0,d.Z)((0,s.Z)({shouldExpand:this.contentDisplayed,showPlayer:Ht,campaign:Ct,answer:a,videoAnswerData:me,videoRef:Vn,alwaysShowVolumeButton:Dn},Ft?{meta:Mt}:{}),{hideCoCreationFeature:Wn,isRecommend:On}))}),(0,h.BX)(We.Z,(0,d.Z)((0,s.Z)((0,d.Z)((0,s.Z)({entityWords:Gn,richContentKey:Pn,className:Z()({"RichContent-mobileBaidu":kn,"RichContent-hasCatalog":(0,Q.Z)(a,"answer"),"AnswerItem-highlight":qn}),truncateDisabled:Un,imperativeRef:this.richContentRef,canAbstract:yn,onToggleExpend:this.handleExpand},Pt&&{expandText:"阅读全文"},en&&Tt&&{expandText:"展开阅读全文"},bn&&rn&&!Tt&&{collapsedHeight:180}),{cover:this.isVideoAnswer&&Nn?null:kt,hasVideo:!Nn&&Boolean(K&&"video"===K.type)||this.isVideoAnswer,videoData:St,handleClickVideoMoreButton:this.handleClickVideoMoreButton,unescapable:Boolean(we),expanded:ge,onPositionStatusChange:this.handlePositionStatusChange,before:Bt,excerpt:cn?cn(O,a):O,html:Ut,prefix:this.renderPrefix(),isNovel:"interactive_novel"===zt,ecommerce:Zn,forceSticky:Wt,isVideoAnswer:this.isVideoAnswer,after:(0,h.BX)("div",{children:[(0,h.tZ)(Xe.v,{answer:a,ua:sn,isAnswerPage:Qn}),(0,h.tZ)(Be.Z,{className:"AnswerItem-CommercialQuestionTail",commercial:E}),!bn&&mt&&(0,h.tZ)(Ue.Z,{contentType:"answer",contentToken:u,author:T}),Nt,Xn&&En&&fe&&(0,h.tZ)($.SV,{children:(0,h.BX)("a",{className:"AnswerItem-editButton",role:"button",tabIndex:0,onClick:this.handleStartEditAnswer,children:[(0,h.tZ)(A.E,{text:!0,center:!0})," ",(0,h.BX)("span",{className:"AnswerItem-editButtonText",children:["修改",Ae&&Ae.editableContent&&"（有未发布的编辑草稿）"]})]})}),!bn&&Xn&&(0,h.tZ)(Fe.Z,{imperativeRef:this.rewardContainerRef,reward:r,currentUser:Xn,rewardInfo:b,isAuthor:En,id:u,author:T,ua:sn,balanceEnable:!1})]}),data:a,onClick:en&&Tt?function(){(Lt||nn||zn)&&bn?(o.setState({autoExpand:!1}),o.richContentRef.current.handleExpand()):bn?te.dd?(o.setState({autoExpand:!1}),o.richContentRef.current.handleExpand()):o.setState({skipModalShow:!0,autoExpand:!1}):o.setState({showWechatExpand:!0,autoExpand:!1})}:Pt?te.dd&&bn?function(){o.richContentRef.current.handleExpand()}:o.createOpenInAppHandler("expand_answer"):o.disableAuth&&en&&o.handleToggleGuide}),an?{limit:74}:{},this.coCreate?{limitWithImage:74}:{}),{zaIds:{expand:hn},children:[Zt&&Cn&&bt&&yt&&!B&&(0,h.tZ)(G.ZP,{className:Z()("ContentItem-rightButton AnswerItem-mainAction AnswerItem-open",{"AnswerItem-mainAction--disabled":"community"===F}),onClick:this.handleUpdateAnswerCollapsed,children:"公开回答"}),Zt&&xe&&!yt&&"brand_special"!==de&&(0,h.tZ)(G.ZP,{className:"ContentItem-rightButton AnswerItem-mainAction AnswerItem-brandQuestionButton",onClick:this.handleUpdateAnswerStick,children:W?"取消精选":"设为精选"}),!this.props.isBaidu&&Jn({componentList:[{name:"vote",component:Zt&&this.renderVoteButton()},{name:"comment",component:Zt&&!(bn&&"answer"!==we)&&(0,h.tZ)(Re.Z,(0,d.Z)((0,s.Z)({onInstance:function(e){return o.commentButton=e},onClick:this.openModal},(bn&&rn&&dn||Fn)&&{onClick:function(e){Wt?o.openModal(e,{commentsShown:!0}):o.createOpenInAppHandler("comment_answer")}}),{commentsShown:rt,commentClosed:U,count:L,positionStatus:ut,zaInfos:{toggleComment:wn,getCommentAction:vn}}),"comment")},{name:"share",component:Zt&&!bn&&(0,h.tZ)(Ge.Z,{disabled:In||xn,id:u,type:"answer",title:k,authorName:T&&T.name,href:this.href,positionStatus:ut,zaShareId:fn,onShare:jn},"share")},{name:"favlist",component:Zt&&!(bn&&"answer"!==we)&&(!Xn||!Xn.isOrg)&&(0,h.tZ)(ze.Z,{onRef:function(e){return o.favButtonRef=e},onClick:this.handleFavlistsShown,label:bn?"":"收藏",disabled:In||xn},"favlist")},!bn&&{name:"thank",component:Zt&&!En&&(0,h.tZ)(Ce.HS,(0,s.Z)({zaInfo:mn,answer:a,disabled:In||xn},this.isLegacyVideoAnswer&&{zVideoId:pe.attachmentId}),"thank")},{name:"sticky",component:!bn&&Yn&&En&&(0,re.U)(Xn)&&(0,h.tZ)(G.ZP,{preset:"plain",onClick:An,icon:this.props.isSticky?g.TX:C.rh,label:this.props.isSticky?"取消置顶":"置顶"},"sticky")},{name:"options",component:bn&&rn||Zt&&this.renderOptions()},{name:"settings",component:bn&&rn||this.renderSettings()},{name:"annotation",component:!mt&&(0,h.tZ)(be.Z,{annotationDetail:le},"annotation")}]})]}))]}):Nt,qt&&!Vt&&(0,h.tZ)(Ee.Z,{content:Dt,type:"answer",urlToken:String(u)}),Bn&&Tn.startsWith("/question")&&Wt&&(0,h.tZ)("div",{role:"tablist",tabIndex:0,onClick:this.handleClickCommentsPreview,onKeyDown:function(e){"Enter"===e.key&&o.handleClickCommentsPreview(e)},children:(0,h.tZ)(j.Z,{parent:a})}),(0,h.tZ)(P.pS,{ref:this.zaRef}),(0,h.tZ)(Me.Z,{shown:rt,parent:a,byComment:ve,commentPattern:dt,autoFocus:st,onClose:this.closeModal,onComment:$n}),(0,h.tZ)(He.y,{type:"answer",urlToken:u,shown:nt,onClose:this.handleReportHide,zaEnabled:!0}),(0,h.tZ)(N.Z,{addAnnotation:Qe,onClose:this.handleCloseAddAnnotationModal,shown:lt,type:te.R8,urlToken:u,showNotification:je}),(0,h.tZ)(z.Z,{cancelAnnotation:Ke,onClose:this.handleCloseCancelAnnotationModal,shown:ct,type:te.R8,urlToken:u,showNotification:je}),Xn&&En&&(0,h.tZ)(Te.Z,{title:"你确定要删除自己的答案吗？",subtitle:"答案内容不会被永久删除，你还可以撤消本次删除操作。",shown:tt,onCancel:this.closeDeleteModal,onSubmit:this.handleDeleteAnswer}),Ie&&(0,h.tZ)(Te.Z,{title:"隐藏答案",subtitle:"隐藏后该回答将不展示也不流通，是否确定隐藏？",shown:ot,onCancel:this.handleCollapseModalHide,onSubmit:this.handleUpdateAnswerCollapsed}),(0,h.tZ)(Oe.E,{id:u,type:"answer",shown:it,onClose:this.handleFavlistHide,zaEnabled:!0}),bn&&this.state.guideShown&&(0,h.tZ)(ee.Z,{redirectUrl:this.href,buttons:[nn?{name:"wechat",text:"快速登录",fill:"#fff"}:"zhihu"],urlScheme:(0,ae.MN)({type:"answer",id:u}),onClose:this.handleToggleGuide}),(0,h.tZ)(Ne.Z,{notification:he,onRead:function(e){Sn("answer",u,e)},onUseAdmire:function(){o.rewardContainerRef.current.activateReward()},onUseRecommend:function(){var e=o.props.postToolsRecommend;D.Z.confirm((0,h.tZ)("div",{style:{textAlign:"center"},children:"该推荐将使用本月的 1 次推荐次数。"}),{title:"确定是否推荐？"}).then((function(){return e("answer",String(u))}),(function(){}))}}),(0,h.tZ)(Le.Z,{show:wt&&!Lt&&bn&&!nn&&!te.dd,id:a.id,type:a.type,onCancel:function(){o.setState({showWechatExpand:!1},(function(){vt||o.richContentRef.current.handleExpand()}))},onSubmit:function(){o.setState({showWechatExpand:!1}),nn?gt?o.createOpenInAppHandler(vt?"expand_answer2":"expand_answer1")():o.setState({shownLoadingBar:!0}):o.createOpenInAppHandler(vt?"expand_answer2":"expand_answer1")()}}),(0,h.tZ)(_e.Z,{show:ft&&!te.dd,id:a.id,type:a.type,onCancel:function(){o.setState({skipModalShow:!1},(function(){o.richContentRef.current.handleExpand()}))},onSubmit:function(){o.createOpenInAppHandler("expand_answer",tn||on)()}}),(0,h.tZ)(qe.Z,{show:At&&bn})]})},(0,a.Z)(t,[{key:"isPaidAnswer",get:function(){return"paid"===this.props.answer.answerType}},{key:"isVideoAnswer",get:function(){var e=this.props.answer.attachment;return 2===(null==e?void 0:e.type)||"zvideo"===(null==e?void 0:e.type)||"video"===(null==e?void 0:e.type)}},{key:"isLegacyVideoAnswer",get:function(){var e=this.props.answer.attachment;return"zvideo"===(null==e?void 0:e.type)}},{key:"isAuthorInGeneral",get:function(){var e=this.props,n=e.isAuthor,t=e.isSubAuthor,o=e.hideCoCreationFeature;return n||t&&!o}},{key:"contentDisplayed",get:function(){var e=this.props.relatedTo,n=this.state.contentExpanded;return Boolean(e||n)}},{key:"coCreate",get:function(){var e=this.props,n=e.answer.creationRelationship,t=e.hideCoCreationFeature;return Boolean(!t&&(0,X.HE)(n))}},{key:"href",get:function(){var e=this.props.answer,n=e.id,t=e.question.id;return"//".concat(ne.Z.wwwHost,"/question/").concat(t,"/answer/").concat(n)}}]),t}(p.PureComponent);cn.contextTypes={startAddAnswer:I().func},cn.propTypes={relatedTo:I().oneOf(["question","answer"]),editable:I().bool,preset:I().oneOf(["special-plain","plain","primary"]),lessExcerpt:I().bool,shareVideoDetail:I().object,formatContent:I().func,renderExtraOptions:I().func,zaInfos:I().object,onToggleExpand:I().func,useNewLabels:I().bool,renderActionButtons:I().func,canAbstract:I().bool,trackPromotionClick:I().func,isSearchSpecialSource:I().bool,hideCommercialInviteLabel:I().bool,hideCoCreationFeature:I().bool},cn.defaultProps={editable:!1,canAbstract:!1,isSearchSpecialSource:!1,preset:"primary",zaInfos:{},renderActionButtons:Ce.W9,shouldAlwaysShowPlayer:!1,hideCoCreationFeature:!1},n.Z=(0,M.compose)((0,ge.Ib)((function(e){var n=e.answer;return{content:{type:"Answer",token:String(n.id)}}})),(0,V.a)((function(e){var n=e.answer,t=e.trackCardShow,o=void 0===t||t,i=e.zaInfos,a=void 0===i?{}:i;return(0,d.Z)((0,s.Z)({module:"AnswerItem",card:{has_image:Boolean(n.thumbnailExtraInfo&&"image"===n.thumbnailExtraInfo.type),has_video:Boolean(n.thumbnailExtraInfo&&"video"===n.thumbnailExtraInfo.type),content:{type:"Answer",token:n.id&&n.id.toString(),upvote_num:n.voteupCount,comment_num:n.commentCount,publish_timestamp:new Date(n.createTime).getTime(),parent_token:n.question&&n.question.id.toString(),author_member_hash_id:n.author&&n.author.id,video_id:n.thumbnailExtraInfo&&n.thumbnailExtraInfo.videoId}},content:{type:"Answer",token:n.id}},a.index&&{index:a.index},a.cardShow&&{view:{id:a.cardShow}}),{trackCardShow:o})})),E.withRouter,se.Z,(0,m.$_)({dataPath:"answer"}),m.OW,(0,x.connect)((function(e,n){var t,o=e.entities.drafts,i=void 0===o?{}:o,a=e.question,r=(void 0===a?{}:a).draftStatus,s=e.answers,d=void 0===s?{}:s,l=d.paidContent,c=void 0===l?{}:l,u=d.entityWords,h=void 0===u?{}:u,p=e.reward,m=e.switches,w=e.video,f=(void 0===w?{}:w).shareVideoDetail,v=e.env,A=v.edition,g=v.userAgent,C=n.answer,S=n.relatedTo,Z=n.location.pathname,b=Z.split("/"),y=!1,k=!0;!b[1]||"org"!==b[1]&&"people"!==b[1]||(y=b[2]&&-1!==dn.indexOf(b[2]),k=!1);var I,x=(0,M.compose)(sn,rn)(ln(e,n)),E=(0,he.ib)(e),R=["question","answer"].includes(S),B=(0,pe.H8)(e)&&R,T=(0,pe.cq)(e),P=g.Mobile,N=g.Qzone,z=P&&T&&!N,V=(0,K.YJ)(x.creationRelationship),D=(0,he.pG)(e,V),_=(null!==(I=null===(t=C.relationship)||void 0===t?void 0:t.isAuthor)&&void 0!==I?I:(0,he.pG)(e,C.author))&&!D;return{entityWords:h[C.id],draft:C&&i["question_".concat(C.question.id)],draftStatus:null==r?void 0:r[C.question.id],answer:x,ua:(0,pe.Uh)(e),pathname:Z,xiaomi:A.xiaomi,isShenma:A.shenma||/quark/gi.test(e.env.userAgent.origin)||g.UC,reward:p,switches:m,isHuman:B,shouldOia:(0,pe.XE)(e)&&!y,shouldSpecialOia:(0,pe.cq)(e)&&!y,isSpecialQuestionOrAnswer:(0,pe.hV)(e,{type:R&&S,id:R?"answer"===S?C.id:C.question.id:""}),isMobile:(0,pe.Hu)(e),isWechat:e.env.userAgent.Wechat,isHuaweiBrowser:/huaweibrowser/gi.test(e.env.userAgent.origin)||/huawei/gi.test(e.env.userAgent.origin)&&!e.env.userAgent.UC&&!e.env.userAgent.Wechat&&!e.env.userAgent.MQQBrowser&&!/quark/gi.test(e.env.userAgent.origin)&&!/baidu/gi.test(e.env.userAgent.origin),isHonor:/honor/gi.test(e.env.userAgent.origin)&&/MQQBrowser/gi.test(e.env.userAgent.origin),concernedUpvoters:(0,de.V7)(e,{id:C.id}),currentUser:E,shareVideoDetail:f,isBrandAnswer:(0,de.eP)(C),permission:(0,we.hh)(e),ecommerce:(0,O.G_)(e,{type:"answer",urlToken:String(C.id)}),isBaidu:(0,pe.XE)(e)&&A.baidu,showCommentForOia:(0,pe.XE)(e),blockReading:z,paidContent:c,isMuteSpecial:(0,we.gW)(x.question),isMuteFreeze:(0,we.SZ)(x.question),isAuthor:_,isSubAuthor:D,isQuestionPage:k}}),{updateAnswerReshipmentSettings:de.eu,updateAnswerCommentPermission:de.iM,updateAnswerCollapsed:de.ON,updateAnswerStick:de.Vc,deleteAnswer:de.G,restoreAnswer:de.f0,updateAnswer:de.p3,loadAnswerForSettings:de.Hh,showNotification:me.c0,addAnnotation:le.u,cancelAnnotation:le.e,addRewardTagline:fe.OC,updateAnswerReward:de.fT,loadAnswerConcernedVoters:de.OC,fillCurrentUserIfNeeded:he.sF,loadVideoDetails:ve.hK,readContentRightsNotification:ce.Uq,postToolsRecommend:ue.XX4,showMobileSignInModal:we.Ky,loadAnswerEntityWords:de.Pe}),Ve.QV,(0,Ze._)({dataPath:"answer"}))(cn)}}]);
//# sourceMappingURL=lib-2ec050f6.app.cd2e59ea5fa9236e486a.js.map