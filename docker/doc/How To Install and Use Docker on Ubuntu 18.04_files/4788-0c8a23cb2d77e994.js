(self.webpackChunk_N_E=self.webpackChunk_N_E||[]).push([[4788],{65602:function(e,t,n){"use strict";n.d(t,{Z:function(){return ae}});var r=n(27812),o=n(50029),i=n(16835),a=n(87794),l=n.n(a),s=n(67294),c=n(5152),d=n.n(c),u=n(41664),p=n.n(u),m=n(11163),f=n(88134),h=n(45697),g=n.n(h);function x(){return x=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e},x.apply(this,arguments)}function y(e,t){if(null==e)return{};var n,r,o=function(e,t){if(null==e)return{};var n,r,o={},i=Object.keys(e);for(r=0;r<i.length;r++)n=i[r],t.indexOf(n)>=0||(o[n]=e[n]);return o}(e,t);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);for(r=0;r<i.length;r++)n=i[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(o[n]=e[n])}return o}var b=(0,s.forwardRef)((function(e,t){var n=e.color,r=void 0===n?"currentColor":n,o=e.size,i=void 0===o?24:o,a=y(e,["color","size"]);return s.createElement("svg",x({ref:t,xmlns:"http://www.w3.org/2000/svg",width:i,height:i,viewBox:"0 0 24 24",fill:"none",stroke:r,strokeWidth:"2",strokeLinecap:"round",strokeLinejoin:"round"},a),s.createElement("path",{d:"M20.59 13.41l-7.17 7.17a2 2 0 0 1-2.83 0L2 12V2h10l8.59 8.59a2 2 0 0 1 0 2.82z"}),s.createElement("line",{x1:"7",y1:"7",x2:"7.01",y2:"7"}))}));b.propTypes={color:g().string,size:g().oneOfType([g().string,g().number])},b.displayName="Tag";var v=b,w=n(23939),C=n(33606),j=n(17053),k=n(98261),S=n(6944),Z=n(21474),P=n(76427),_=n(88723),O=n(57054),T=n(81042),N=n(9751),I=n(82802),E=n(47811),L=n(55707),z=n(37797),M=z.ZP.div.withConfig({displayName:"UpvoteSyles__StyledUpvoteContainer",componentId:"sc-1it9y7o-0"})(["align-items:center;cursor:pointer;display:flex;flex-direction:column;"]),A=z.ZP.div.withConfig({displayName:"UpvoteSyles__StyledUpvoteCount",componentId:"sc-1it9y7o-1"})(["color:",";font-size:14px;line-height:1;margin-top:4px;"],f.ZP.gray5),U=n(85893),D=function(e){var t=e.upvotableId,n=e.upvotableType,r=(0,O.Z)(),i=(0,L.N)().setNeedLogIn,a=(0,s.useState)(null),c=a[0],d=a[1],u=(0,s.useCallback)((0,o.Z)(l().mark((function e(){var o;return l().wrap((function(e){for(;;)switch(e.prev=e.next){case 0:if(r.token){e.next=3;break}return i(!0),e.abrupt("return");case 3:if(!c.upvoted){e.next=9;break}return e.next=6,(0,C.j_)(r.token,t,n);case 6:e.t0=e.sent,e.next=12;break;case 9:return e.next=11,(0,C.VE)(r.token,t,n);case 11:e.t0=e.sent;case 12:o=e.t0,d(o);case 14:case"end":return e.stop()}}),e)}))),[r,t,n,c,i]);return(0,s.useEffect)((function(){r.token?(0,C.lA)(r.token,t,n).then((function(e){return d(e)})):(0,j.lA)(t,n).then((function(e){return d(e)}))}),[r,t,n]),(0,U.jsxs)(M,{children:[null!==c&&void 0!==c&&c.upvoted?(0,U.jsxs)(U.Fragment,{children:[(0,U.jsx)(I.Z,{size:20,color:f.ZP.red2}),(0,U.jsx)(E.Z,{size:24,color:f.ZP.red2,fill:f.ZP.red2,onClick:u})]}):(0,U.jsxs)(U.Fragment,{children:[(0,U.jsx)(I.Z,{size:20,color:f.ZP.gray5}),(0,U.jsx)(E.Z,{size:24,color:f.ZP.gray5,onClick:u})]}),(0,U.jsx)(A,{children:null!==c&&void 0!==c&&c.count?c.count.toLocaleString():""})]})},F=n(97020),B=n(17534),R=n(87288),H=z.ZP.div.withConfig({displayName:"CommentStyles__StyledCommentContainer",componentId:"sc-gn53o-0"})(["border:1px solid ",";border-radius:24px;margin:0 0 32px;"," "," "," "," "," "," "," overflow-x:auto;padding:24px 33.5px;","{padding:21px;}"],f.ZP.gray7,(function(e){return 0===e.voteable&&"\n    display: grid;\n    grid-template-columns: 24px minmax(0, 1fr);\n    grid-template-rows: min-content min-content;\n    gap: 0 24px;\n  "}),(function(e){return e.align&&"left"===e.align?"padding-left: 0px;":"padding-left: 15px;"}),(function(e){return e.accepted&&"\n      background-color: ".concat((0,f.E9)(f.ZP.blue5,.35),";\n    ")}),(function(e){return e.pinned&&"\n      background-color: ".concat((0,f.E9)(f.ZP.green5,.5),";\n    ")}),(function(e){return"trashed"===e.state&&"\n    background-color: ".concat((0,f.E9)(f.ZP.red2,.2),";\n    border-color: ").concat((0,f.E9)(f.ZP.red2,.6),";\n  ")}),(function(e){return"spam"===e.state&&"\n    background-color: ".concat((0,f.E9)(f.ZP.orange2,.2),";\n    border-color: ").concat((0,f.E9)(f.ZP.orange2,.6),";\n  ")}),(function(e){return"under_review"===e.state&&"\n    background-color: ".concat((0,f.E9)(f.ZP.blue2,.2),";\n    border-color: ").concat((0,f.E9)(f.ZP.blue2,.6),";\n  ")}),(0,B.X)(B.A.tablet)),q=z.ZP.div.withConfig({displayName:"CommentStyles__StyledCommentUpvoteContainer",componentId:"sc-gn53o-1"})(["","{grid-row:span 2;}"],(0,B.X)(B.A.tablet,"min")),W=z.ZP.div.withConfig({displayName:"CommentStyles__StyledCommentMeta",componentId:"sc-gn53o-2"})(["display:flex;flex-direction:column;flex-grow:1;"]),X=z.ZP.div.withConfig({displayName:"CommentStyles__StyledCommentMetaContainer",componentId:"sc-gn53o-3"})(["align-items:center;display:flex;margin-bottom:16px;position:relative;","{align-items:flex-start;flex-direction:column;}"],(0,B.X)(B.A.tablet)),V=z.ZP.div.withConfig({displayName:"CommentStyles__StyledCommentMetaNameAndDate",componentId:"sc-gn53o-4"})(["align-items:center;color:",";display:flex;flex-wrap:wrap;font-size:16px;line-height:1.5;margin-right:auto;","{align-items:flex-start;flex-direction:column;span{display:none;}}span{margin:0 5px;}"],f.ZP.gray4,(0,B.X)(B.A.tablet)),Y=z.ZP.a.withConfig({displayName:"CommentStyles__StyledCommentMetaName",componentId:"sc-gn53o-5"})(["color:",";cursor:pointer;display:block;font-weight:500;"],f.ZP.blue2),G=z.ZP.a.withConfig({displayName:"CommentStyles__StyledCommentMetaDate",componentId:"sc-gn53o-6"})(["color:inherit;text-decoration:none;&:hover{text-decoration:underline;}"]),$=z.ZP.div.withConfig({displayName:"CommentStyles__StyledCommentBody",componentId:"sc-gn53o-7"})(["color:",";font-size:16px;","{grid-column:span 2;}"," ",""],f.ZP.gray4,(0,B.X)(B.A.tablet),(function(e){return!e.expanded&&"\n      display: -webkit-box;\n      -webkit-line-clamp: 2;\n      -webkit-box-orient: vertical;\n      overflow: hidden;\n      margin-bottom: 0;\n    "}),(function(e){return!e.expanded&&e.isNested&&"display: none;"})),J=(z.ZP.div.withConfig({displayName:"CommentStyles__StyledUserReportCommentContainer",componentId:"sc-gn53o-8"})(["display:flex;flex-direction:column;margin-bottom:16px;&:last-of-type{margin-bottom:0;}a{margin-left:0;text-decoration:none;:hover{border-bottom:none;}}"]),z.ZP.ul.withConfig({displayName:"CommentStyles__StyledCommentActions",componentId:"sc-gn53o-9"})(["align-items:center;list-style-type:none;margin:24px 0 0;"," padding:0;&:empty{display:none;}li{margin-right:16px;&:last-child{margin-right:0;}}"],(function(e){return e.expanded?"display: flex;":"display: none;"}))),K=z.ZP.button.withConfig({displayName:"CommentStyles__StyledCommentAction",componentId:"sc-gn53o-10"})(["background:none;border:none;color:",";cursor:pointer;display:inline-block;font-size:13px;font-weight:400;line-height:",";margin:0;padding:0;text-decoration:underline;transition:color 0.2s ease-in-out;vertical-align:top;&:last-child{margin-right:0;}&:not(:disabled):hover{color:",";}&:disabled{color:",";cursor:not-allowed;}b{font-weight:500;}"],f.ZP.blue2,24/13,f.ZP.blueHover,f.ZP.gray4),Q=z.ZP.div.withConfig({displayName:"CommentStyles__StyledPinnedAnswerLabel",componentId:"sc-gn53o-11"})(["align-items:center;color:",";display:flex;margin-right:24px;","{margin-top:14px;}span{font-family:",";font-size:13px;font-weight:800;line-height:",";margin-left:8px;text-transform:uppercase;}"],f.ZP.blue2,(0,B.X)(B.A.tablet),(0,R.Z)("code"),24/13),ee=z.ZP.div.withConfig({displayName:"CommentStyles__StyledCommentChildren",componentId:"sc-gn53o-12"})(["border-left:1.5px solid ",";margin-top:16px;&:empty{display:none;}","{border:0;margin-bottom:12px;padding:12px 0 0 24px;}&:last-child{","{margin-bottom:0;}}"],f.ZP.gray6,H,H),te=z.ZP.div.withConfig({displayName:"CommentStyles__StyledCommentChildrenForm",componentId:"sc-gn53o-13"})(["padding:24px 0;"]),ne=z.ZP.div.withConfig({displayName:"CommentStyles__StyledError",componentId:"sc-gn53o-14"})(["background:#faa;border-radius:3px;margin:0 0 40px;padding:20px;"]),re=z.ZP.button.withConfig({displayName:"CommentStyles__StyledExpandButton",componentId:"sc-gn53o-15"})(["align-items:center;background:none;border:0;border-radius:0;color:",";cursor:pointer;display:flex;font-size:13px;line-height:",";margin:0;"," overflow:hidden;padding:0;text-decoration:underline;span{display:block;height:24px;"," position:relative;width:24px;}&:hover{color:",";span{color:",";}}svg{left:50%;"," position:absolute;top:50%;transition:transform 300ms ease-in-out;width:12px;}"],f.ZP.blue2,24/13,(function(e){return!e.actionItem&&"\n    ".concat((0,B.X)(B.A.tablet)," {\n      position: absolute;\n      right: 0;\n      top: 0;\n    }\n  ")}),(function(e){return e.expanded?"\n      color: ".concat(f.ZP.gray2,";\n    "):"\n      color: ".concat(f.ZP.gray5,";\n    ")}),f.ZP.blueHover,f.ZP.gray2,(function(e){return e.expanded?"\n      transform: translate(-50%, -50%);\n    ":"transform: translate(-50%, -50%) rotate(180deg);"})),oe=d()((function(){return Promise.resolve().then(n.bind(n,65861))}),{loadableGenerated:{webpack:function(){return[65861]}}}),ie=(0,s.forwardRef)((function(e,t){var n,a,c=e.record,d=e.topLevelType,u=e.topLevel,h=e.handleUpdatedTopLevel,g=e.parent,x=e.align,y=e.accepted,b=e.expanded,I=e.pinned,E=e.loadNested,L=e.replyable,z=e.handleUpdatedComment,M=e.urlFormatter,A=e.upvotable,B=e.users,R=(0,O.Z)(),ae=(0,m.useRouter)(),le=(0,T.ZP)(),se=(0,i.Z)(le,2),ce=se[0],de=se[1],ue=(0,s.useState)(),pe=ue[0],me=ue[1],fe=(0,s.useState)(!1),he=fe[0],ge=fe[1],xe=(0,s.useState)(!1),ye=xe[0],be=xe[1],ve=(0,s.useState)(b),we=ve[0],Ce=ve[1],je=(0,s.useState)(!1),ke=je[0],Se=je[1],Ze=R.permissions.has(P.P.flags.MANAGE_COMMENTS)||R.permissions.has(P.P.flags.ADMINISTRATOR),Pe=(null===(n=R.user)||void 0===n?void 0:n.id)===c.user_id||Ze,_e=(null===(a=R.user)||void 0===a?void 0:a.id)===(null===u||void 0===u?void 0:u.user_id),Oe=new Date-new Date(c.created_at)<36e5,Te=(0,s.useState)(null),Ne=Te[0],Ie=Te[1],Ee=(0,s.useState)([]),Le=Ee[0],ze=Ee[1],Me=(0,s.useState)(c),Ae=Me[0],Ue=Me[1],De=(0,s.useState)(E?0:"last"),Fe=De[0],Be=De[1],Re=(0,s.useState)(!1),He=Re[0],qe=Re[1],We=(0,s.useState)(!1),Xe=We[0],Ve=We[1],Ye=(0,s.useState)(!1),Ge=Ye[0],$e=Ye[1],Je=function(e){console.error(e),Ie(e.message)},Ke=(0,s.useCallback)(function(){var e=(0,o.Z)(l().mark((function e(t){return l().wrap((function(e){for(;;)switch(e.prev=e.next){case 0:if(!ye){e.next=2;break}return e.abrupt("return");case 2:be(!0),(0,C.uA)(R.token,c.id,t).then((function(e){return e&&z(e)})).catch(Je).finally((function(){return be(!1)}));case 4:case"end":return e.stop()}}),e)})));return function(t){return e.apply(this,arguments)}}(),[ye,R.token,c.id,z]),Qe=function(e){ze((function(t){return t.map((function(t){return t.id===e.id?e:t}))}))},et=(0,s.useCallback)(function(){var e=(0,o.Z)(l().mark((function e(t){return l().wrap((function(e){for(;;)switch(e.prev=e.next){case 0:if(!ye){e.next=2;break}return e.abrupt("return");case 2:be(!0),(0,C.ZY)(R.token,u.slug,t).then((function(e){h(e)})).catch(Je).finally((function(){return be(!1)}));case 4:case"end":return e.stop()}}),e)})));return function(t){return e.apply(this,arguments)}}(),[ye,R.token,u.slug,h]);return(0,s.useEffect)((function(){"last"!==Fe&&(0,j.xP)("comment",c.id,{type:"comment",page:Fe,per_page:S.oA.commentsPerPage}).then((function(e){ze((function(t){return t.concat(e)})),e.length<S.oA.commentsPerPage?Be("last"):Be(Fe+1)}))}),[c,Fe]),(0,s.useEffect)((function(){Pe&&"trashed"===c.state&&(0,C._g)(R.token,c.id).then((function(e){Ue(e)})).catch((function(e){return console.error(e)}))}),[R,Pe,c]),(0,s.useEffect)((function(){var e;ae.isReady&&me(parseInt(null===(e=ae.query)||void 0===e?void 0:e.comment,10))}),[ae]),(0,s.useEffect)((function(){de.current&&!he&&(ce(),ge(!0))}),[de,ce,he]),(0,U.jsxs)(H,{align:x,accepted:y,pinned:I,state:c.state,voteable:A?0:1,isExpanded:we,ref:function(e){t&&(t.current=e),pe===c.id&&(de.current=e)},children:[A&&(0,U.jsx)(q,{children:(0,U.jsx)(D,{upvotableId:c.id,upvotableType:"comment"})}),(0,U.jsx)(W,{children:(0,U.jsxs)(X,{children:[(0,U.jsxs)(V,{children:[(0,U.jsx)(p(),{href:(0,_.F7)("user",c.user.slug),passHref:!0,children:(0,U.jsx)(Y,{children:(0,Z.Z)(c.user)})}),(0,U.jsx)("span",{children:" \u2022 "}),(0,U.jsx)(p(),{href:M(c.id),passHref:!0,children:(0,U.jsx)(G,{children:(0,k.Z)(c.created_at)})})]}),(I||y)&&(0,U.jsxs)("div",{children:[I&&(0,U.jsxs)(Q,{children:[(0,U.jsx)(v,{height:14,width:14,color:f.ZP.blue2}),(0,U.jsx)("span",{children:"Pinned Answer"})]}),y&&(0,U.jsxs)(Q,{children:[(0,U.jsx)(w.Z,{height:14,width:14,color:f.ZP.blue2}),(0,U.jsx)("span",{children:"Accepted Answer"})]})]}),(0,U.jsxs)(re,{isNested:"nested"===x,type:"button",expanded:we,onClick:function(){return Ce(!we)},children:["nested"===x&&(we?"Hide reply":"Show reply"),(0,U.jsx)("span",{children:(0,U.jsx)("svg",{fill:"none",height:"9",viewBox:"0 0 15 9",width:"15",xmlns:"http://www.w3.org/2000/svg",children:(0,U.jsx)("path",{d:"m1.5 8.06543 6-6 6 6",stroke:"currentColor",strokeWidth:"2"})})})]})]})}),(0,U.jsxs)($,{expanded:we,children:[Xe?(0,U.jsx)(F.Z,{topLevelType:d,topLevel:u,parentType:c.parent_type,parent:g||u,showHeader:!1,record:Ae,type:c.type,buttonText:"Update ".concat(c.type),onSave:function(e){Ve((function(e){return!e})),Ue(e)},usersThread:[].concat((0,r.Z)(B),[c.user.slug])}):(0,U.jsx)($,{expanded:we,isNested:"nested"===x,children:(0,U.jsx)(oe,{content:Ae.content})}),(0,U.jsxs)(J,{expanded:we,children:[Le.length>0&&(0,U.jsx)("li",{children:(0,U.jsxs)(re,{type:"button",actionItem:!0,expanded:ke,onClick:function(){return Se(!ke)},children:[ke?"Hide replies":"Show replies",(0,U.jsx)("span",{children:(0,U.jsx)("svg",{fill:"none",height:"9",viewBox:"0 0 15 9",width:"15",xmlns:"http://www.w3.org/2000/svg",children:(0,U.jsx)("path",{d:"m1.5 8.06543 6-6 6 6",stroke:"currentColor",strokeWidth:"2"})})})]})}),L&&d&&u&&null==c.comments_locked_at&&(0,U.jsx)("li",{children:(0,U.jsx)(K,{onClick:function(){return qe((function(e){return!e}))},children:"Reply"})}),R.user&&(0,U.jsx)("li",{children:(0,U.jsx)(N.Z,{record:c,reportedType:"Comment",auth:R,text:"Report",size:"small",isReportModalOpen:Ge,setIsReportModalOpen:$e})}),(Pe&&Oe&&"published"===c.state||Ze)&&(0,U.jsx)("li",{children:(0,U.jsx)(K,{onClick:function(){return Ve((function(e){return!e}))},children:"Edit"})}),(Pe&&Oe||Ze)&&"trashed"!==c.state&&(0,U.jsx)("li",{children:(0,U.jsx)(K,{onClick:function(){return Ke({state:"trashed"})},disabled:ye,children:"Delete"})}),"published"!==c.state&&Ze&&(0,U.jsx)("li",{children:(0,U.jsx)(K,{onClick:function(){return Ke({state:"published"})},disabled:ye,children:"Publish"})}),Ze&&(0,U.jsxs)(U.Fragment,{children:[(0,U.jsx)("li",{children:(0,U.jsxs)(K,{onClick:function(){return Ke({comments_locked_at:null===c.comments_locked_at?new Date:null})},disabled:ye,children:[null===c.comments_locked_at?"Lock":"Unlock "," ","All Comments"]})}),(0,U.jsx)("li",{children:(0,U.jsx)(K,{onClick:function(){return Ke({state:"spam"})},disabled:ye,children:"Spam"})}),"question"===c.top_level_type&&"answer"===c.type&&(0,U.jsx)("li",{children:(0,U.jsx)(K,{onClick:function(){return et({pinned_id:I?null:c.id})},disabled:ye,children:I?"Unpin":"Pin"})})]}),"question"===c.top_level_type&&"answer"===c.type&&(Ze||_e)&&(0,U.jsx)("li",{children:(0,U.jsxs)(K,{onClick:function(){return et({accepted_id:y?null:c.id})},disabled:ye,children:[y?"Unmark":"Mark"," ","as accepted"]})})]}),Ne&&(0,U.jsxs)(ne,{children:[(0,U.jsx)("b",{children:"An error occurred:"})," ",Ne]}),L&&He&&d&&u&&(0,U.jsx)(te,{children:(0,U.jsx)(F.Z,{topLevelType:d,topLevel:u,parentType:"comment",parent:c,type:"comment",onSave:function(e){ze((function(t){return t.concat(e)})),qe(!1)},showHeader:!1,usersThread:[].concat((0,r.Z)(B),[c.user.slug])})}),ke&&(0,U.jsx)(ee,{children:Le.map((function(e){return(0,U.jsx)(ie,{record:e,topLevelType:d,topLevel:u,handleUpdatedTopLevel:h,parent:c,align:"nested",expanded:!0,loadNested:E,replyable:L,handleUpdatedComment:Qe,users:[].concat((0,r.Z)(B),[c.user.slug])},e.id)}))})]})]},c.id)})),ae=ie;ie.displayName="Comment",ie.defaultProps={topLevel:null,handleUpdatedTopLevel:function(){},parent:null,align:null,accepted:!1,pinned:!1,loadNested:!1,replyable:!1,upvotable:!1,expanded:!0,urlFormatter:function(){return"#"},users:[]}},68605:function(e,t,n){"use strict";n.d(t,{B:function(){return o}});var r=n(88134),o=n(37797).ZP.button.withConfig({displayName:"LoadMoreButtonStyles__StyledLoadMoreButton",componentId:"sc-1my1ou7-0"})(["background:",";border:1px solid ",";border-radius:10px;box-shadow:none;color:",";cursor:pointer;font-size:16px;line-height:24px;margin:1rem auto;padding:8px 20px;text-align:center;&:hover{background:",";box-shadow:0 10px 20px ",";color:",";transition:box-shadow 0.25s linear,-webkit-box-shadow 0.25s linear;}"],r.ZP.white,r.ZP.grayBorder,r.ZP.gray3,r.ZP.blueHover,(0,r.E9)(r.ZP.blueDark,.1),r.ZP.white)},21346:function(e,t,n){"use strict";var r=n(37797),o=n(68605),i=n(85893),a=function(e){var t=e.visible,n=e.onClick,r=e.message,o=e.styles;return t&&(0,i.jsx)(l,{type:"button",onClick:n,$_css:o,children:r})};t.Z=a,a.defaultProps={message:"Load More",styles:null};var l=(0,r.ZP)(o.B).withConfig({displayName:"LoadMoreButton___StyledStyledLoadMoreButton",componentId:"sc-1xkxrc2-0"})(["",""],(function(e){return e.$_css}))},27767:function(e,t,n){"use strict";n.d(t,{Z:function(){return b}});var r=n(59499),o=n(27812),i=n(67294),a=n(16496),l=n.n(a),s=n(95784),c=n(88134),d=n(37797),u=n(62080),p=d.ZP.div.withConfig({displayName:"MarkdownWithMentionsStyles__StyledCommentsUserWrapper",componentId:"sc-11zqajg-0"})(["background-color:",";border-radius:6px;box-shadow:"," 0 1px 4px;left:",";min-width:150px;position:absolute;top:",";z-index:1;"],c.ZP.white,(0,c.E9)(c.ZP.black,.4),(function(e){return"".concat(e.cursorLeft,"px")}),(function(e){return"".concat(e.cursorTop,"px")})),m=d.ZP.li.withConfig({displayName:"MarkdownWithMentionsStyles__StyledLisItem",componentId:"sc-11zqajg-1"})(["background-color:",";border-radius:6px;color:",";transition:background-color 0.3s ease,color 0.3s ease;&:not(:first-child){border-top-left-radius:0;border-top-right-radius:0;}&:not(:last-child){border-bottom-left-radius:0;border-bottom-right-radius:0;}&:hover{background-color:",";color:",";}"],(function(e){return e.selectedUser?c.ZP.blue2:"none"}),(function(e){return e.selectedUser?c.ZP.gray10:c.ZP.gray4}),c.ZP.blue5,c.ZP.gray4),f=(0,d.ZP)(u.Z).withConfig({displayName:"MarkdownWithMentionsStyles__StyledUserMentionButton",componentId:"sc-11zqajg-2"})(["border:none;color:inherit;display:block;font-size:inherit;font-weight:inherit;padding:4px 8px;text-align:left;width:100%;&:not(:disabled):hover{background-color:transparent;}"]),h=n(85893);function g(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function x(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?g(Object(n),!0).forEach((function(t){(0,r.Z)(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):g(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}var y=function(e){var t=e.value,n=e.onChange,r=e.disabled,a=e.hasError,c=e.required,d=e.id,u=e.placeholder,g=e.style,y=e.usersThread,b=(0,i.useState)(!1),v=b[0],w=b[1],C=(0,i.useState)(null),j=C[0],k=C[1],S=(0,i.useState)(0),Z=S[0],P=S[1],_=(0,i.useState)(null),O=_[0],T=_[1],N=(0,i.useState)(null),I=N[0],E=N[1],L=(0,i.useState)(""),z=L[0],M=L[1],A=(0,i.useState)([]),U=A[0],D=A[1],F=(0,i.useRef)();(0,i.useEffect)((function(){D((0,o.Z)(new Set(y.sort())).filter((function(e){return e.toLowerCase().startsWith(z.toLowerCase())})))}),[y,z]);var B=(0,i.useCallback)((function(){T(null),E(null),k(null),M(""),P(0),w(!1)}),[]),R=(0,i.useCallback)((function(e){var r=U[e],o="".concat(t.slice(0,j)).concat(r).concat(t.slice(j,t.length));n(o),F.current.value=o,F.current.focus({preventScroll:!0}),F.current.setSelectionRange(j+r.length,j+r.length),B()}),[U,t,j,n,B]),H=(0,i.useCallback)((function(e){switch(e.key){case"@":if(!v&&F.current===document.activeElement){M(""),w(!0),k(F.current.selectionStart);var t=l()(F.current,F.current.selectionStart);T(t.left),E(t.top+t.height)}break;case"ArrowLeft":v&&F.current.selectionStart<=j&&B();break;default:if(v){if("@"!==F.current.value[j-1]){B();break}var n=F.current.value.substring(j,F.current.selectionEnd);/^[a-z0-9]*$/i.test(n)?M(n):B()}}}),[v,B,j]),q=(0,i.useCallback)((function(e){switch(e.key){case"ArrowDown":v&&(e.preventDefault(),P((function(e){return(e+1)%U.length})));break;case"ArrowUp":v&&(e.preventDefault(),P((function(e){return e>0?e-1:U.length-1})));break;case"Enter":v&&(e.preventDefault(),R(Z));break;case"Escape":v&&(e.preventDefault(),B())}}),[v,Z,U,R,B]);return(0,h.jsxs)("div",{style:x(x({},g),{},{position:"relative"}),onKeyDown:q,onKeyUp:H,children:[v&&(0,h.jsx)(p,{cursorLeft:O,cursorTop:I+65,children:(0,h.jsx)("ul",{children:U.map((function(e,t){return(0,h.jsx)(m,{selectedUser:t===Z,children:(0,h.jsx)(f,{onClick:function(){return R(t)},children:e})},"suggested-".concat(e))}))})}),(0,h.jsx)(s.Z,{value:t,onChange:n,disabled:r,hasError:a,required:c,placeholder:u,id:d,ref:F})]})},b=y;y.defaultProps={disabled:!1,required:!1,hasError:!1,id:null,placeholder:null,style:{},usersThread:[]}},97020:function(e,t,n){"use strict";n.d(t,{Z:function(){return O}});var r=n(50029),o=n(59499),i=n(37797),a=n(87794),l=n.n(a),s=n(67294),c=n(33606),d=n(89136),u=n(57054),p=n(62080),m=n(34531),f=n(27767),h=n(23478),g=n(92985),x=n(88134),y=n(87288),b=i.ZP.form.withConfig({displayName:"CommentFormTemplateStyles__StyledForm",componentId:"sc-1dqa7xz-0"})([""]),v=i.ZP.div.withConfig({displayName:"CommentFormTemplateStyles__StyledFormHeader",componentId:"sc-1dqa7xz-1"})(["color:",";font-size:24px;font-weight:600;line-height:32px;margin-bottom:16px;"],x.ZP.gray2),w=i.ZP.div.withConfig({displayName:"CommentFormTemplateStyles__StyledFormError",componentId:"sc-1dqa7xz-2"})(["background:#faa;border-radius:3px;margin:0 0 40px;padding:20px;"]),C=i.ZP.div.withConfig({displayName:"CommentFormTemplateStyles__StyledButtonBar",componentId:"sc-1dqa7xz-3"})(["margin-top:5px;padding:0;"]),j=(0,i.iv)(["background-color:",";border:0;border-radius:10px;color:",";cursor:pointer;font-size:16px;font-weight:600;line-height:1.5;min-width:192px;padding:8px 32px;text-align:center;&:hover{background-color:",";}"],x.ZP.blue2,x.ZP.white,x.ZP.blueHover),k=i.ZP.div.withConfig({displayName:"CommentFormTemplateStyles__StyledFormNote",componentId:"sc-1dqa7xz-4"})(["margin:20px 0 24px;p{color:",";font-size:16px;line-height:1.5;margin:0 0 16px;strong{color:",";font-family:",";font-size:14px;font-weight:700;}}kbd{background:",";color:",";font-size:0.9em;font-weight:500;padding:0.1em 0.3em;}"],x.ZP.gray5,x.ZP.gray4,(0,y.Z)("code"),x.ZP.grayLighter,x.ZP.gray4),S=n(85893);function Z(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function P(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?Z(Object(n),!0).forEach((function(t){(0,o.Z)(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):Z(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}var _=function(e){var t=e.topLevel,n=e.topLevelType,o=e.parent,i=e.parentType,a=e.onSave,p=e.showHeader,m=e.record,x=e.buttonText,y=e.type,j=e.count,Z=e.usersThread,_=(0,u.Z)(),O=(0,s.useMemo)((function(){return"comment_record_".concat(i,"_").concat(o.id)}),[i,o]),I=(0,s.useState)({content:null===m||void 0===m?void 0:m.content}),E=I[0],L=I[1],z=(0,s.useCallback)((function(e){L((function(t){return P(P({},t),{},{content:e})})),m||(e?(0,d.Pp)(O,{content:e}):(0,d.DC)(O))}),[O,m]),M=(0,s.useState)("hidden"),A=M[0],U=M[1],D=(0,s.useState)(!1),F=D[0],B=D[1],R=(0,s.useState)(null),H=R[0],q=R[1];(0,s.useEffect)((function(){var e=(0,d.L2)(O);e&&!m&&L((function(t){return P(P({},t),e)}))}),[O,m]);var W=function(){var e=(0,r.Z)(l().mark((function e(r){var s,d,u;return l().wrap((function(e){for(;;)switch(e.prev=e.next){case 0:if(r.preventDefault(),!F){e.next=3;break}return e.abrupt("return");case 3:if(B(!0),q(null),s=P(P({},E),{},{parent_id:o.id,parent_type:i,top_level_id:t.id,top_level_type:n,type:y}),d=function(e){console.error(e),B(!1),q(e.message)},null===m||void 0===m||!m.id){e.next=13;break}return e.next=10,(0,c.uA)(_.token,m.id,s).catch(d);case 10:e.t0=e.sent,e.next=16;break;case 13:return e.next=15,(0,c.Yr)(_.token,s).catch(d);case 15:e.t0=e.sent;case 16:if(u=e.t0){e.next=19;break}return e.abrupt("return");case 19:B(!1),q(null),z(""),"published"===u.state?a(u):U(u.state);case 23:case"end":return e.stop()}}),e)})));return function(t){return e.apply(this,arguments)}}(),X=(0,s.useMemo)((function(){var e;return _.token&&!(null===(e=_.user)||void 0===e||!e.email_verified_at)}),[_]);return(0,S.jsxs)("div",{children:[p&&(0,S.jsx)(v,{children:j>0?"".concat(j," Comments"):"Leave a comment"}),(0,S.jsxs)(b,{children:[H&&(0,S.jsxs)(w,{children:[(0,S.jsx)("b",{children:"An error occurred when saving the comment:"})," ",H]}),(null===_||void 0===_?void 0:_.token)&&!X&&(0,S.jsx)(h.Z,{}),(0,S.jsx)(f.Z,{value:E.content||"",onChange:z,disabled:F||!X,required:!0,placeholder:"Leave a comment...",usersThread:Z})]}),(0,S.jsxs)(k,{children:[(0,S.jsxs)("p",{children:["This textbox defaults to using"," ",(0,S.jsx)("strong",{children:"Markdown"})," ","to format your answer."]}),(0,S.jsxs)("p",{children:["You can type"," ",(0,S.jsx)("strong",{children:"!ref"})," ","in this text area to quickly search our full set of"," ","tutorials, documentation & marketplace offerings and insert the link!"]})]}),(0,S.jsxs)(C,{children:[null===_.user?(0,S.jsx)(T,{url:_.signIn,children:"Sign In or Sign Up to Comment"}):(0,S.jsx)(S.Fragment,{children:(0,S.jsx)(N,{onClick:function(e){return W(e)},disabled:F||!X,children:x})}),"hidden"!==A&&(0,S.jsx)(g.Z,{type:"comment",state:A})]})]})},O=_;_.defaultProps={showHeader:!0,record:null,buttonText:"Comment",type:"",count:0};var T=(0,i.ZP)(m.Z).withConfig({displayName:"CommentFormTemplate___StyledButtonLink",componentId:"sc-er5enn-0"})(["",""],j),N=(0,i.ZP)(p.Z).withConfig({displayName:"CommentFormTemplate___StyledButton",componentId:"sc-er5enn-1"})(["",""],j)},81118:function(e,t,n){"use strict";n.d(t,{Z:function(){return p}});var r=n(65602),o=n(21346),i=n(17534),a=n(88134),l=n(37797),s=l.ZP.div.withConfig({displayName:"CommentsTemplateStyles__StyledCommentsContainer",componentId:"sc-k3bvlc-0"})(["display:flex;flex-direction:column;line-height:1.4;margin:0 auto;position:relative;width:100%;","{margin:0;}"],(0,i.X)(i.A.desktop)),c=l.ZP.div.withConfig({displayName:"CommentsTemplateStyles__StyledCommentHeader",componentId:"sc-k3bvlc-1"})(["border:10px ",";border-bottom:solid #e4e8ed;color:",";font-size:20px;font-weight:500;line-height:20px;padding:20px;text-align:center;text-decoration:underline solid ",";text-underline-offset:23px;"],a.ZP.grayLight,a.ZP.blueDark,a.ZP.blueLight),d=n(85893),u=function(e){var t=e.records,n=e.topLevelType,i=e.topLevel,a=e.handleUpdatedTopLevel,l=e.title,u=e.align,p=e.showTitle,m=e.loadNested,f=e.replyable,h=e.expanded,g=e.urlFormatter,x=e.onLoadMore,y=e.handleUpdatedComment,b=e.hasMoreComments,v=e.upvotable,w=e.users;return(0,d.jsxs)(s,{children:[l.length>0&&p&&(0,d.jsxs)(c,{children:[l,"s"]}),t.map((function(e){return(0,d.jsx)(r.Z,{record:e,topLevelType:n,topLevel:i,handleUpdatedTopLevel:a,loadNested:m,align:u,replyable:f,expanded:h,handleUpdatedComment:y,urlFormatter:g,upvotable:v,users:w},e.id)})),b&&(0,d.jsx)(o.Z,{onClick:x,visible:t.length>0,message:"Load More ".concat(l,"s")})]})},p=u;u.defaultProps={align:null,title:"Comment",showTitle:!1,loadNested:!1,replyable:!1,expanded:!0,urlFormatter:function(){return"#"},topLevel:null,handleUpdatedTopLevel:function(){},onLoadMore:function(){},hasMoreComments:!1,upvotable:!1}},23478:function(e,t,n){"use strict";n.d(t,{Z:function(){return m}});var r=n(67294),o=n(41601),i=n(90352),a=n(88134),l=n(37797),s=n(62080),c=l.ZP.div.withConfig({displayName:"EmailNotVerifiedCalloutStyles__StyledNotVerifiedCallout",componentId:"sc-s04hs4-0"})(["border:1px solid ",";border-radius:3px;font-size:16px;margin:"," 0 16px;padding:16px 24px;width:100%;"],a.ZP.red3,(function(e){return e.marginTop||"32px"})),d=(0,l.ZP)(s.Z).withConfig({displayName:"EmailNotVerifiedCalloutStyles__StyledCalloutButton",componentId:"sc-s04hs4-1"})(["display:inline-block;font-size:16px;font-weight:500;padding:8px 16px;"]),u=n(85893),p=function(e){var t=e.marginTop,n=(0,r.useCallback)((function(e){e.preventDefault(),window.location.href=(0,o.Z)(window.location)}),[]);return(0,u.jsxs)(c,{marginTop:t,children:[(0,u.jsxs)("div",{children:["You need to verify your email for this account before you can post."," ","Go"," ",(0,u.jsx)(i.Z,{url:"https://cloud.digitalocean.com/",children:"here"})," ","to resend the verification email."]}),(0,u.jsxs)("div",{children:["Already verified your email?"," ",(0,u.jsx)(d,{onClick:n,children:"Refresh authentication"})]})]})},m=p;p.defaultProps={marginTop:null}},92985:function(e,t,n){"use strict";n.d(t,{Z:function(){return i}});var r=n(37797).ZP.div.withConfig({displayName:"SpamErrorTemplateStyles__StyledSpamError",componentId:"sc-a41zpz-0"})(["background:#ffeaea;border-radius:5px;box-sizing:border-box;color:#b62929;font-size:18px;margin-bottom:10px;margin-top:30px;padding:17px;position:relative;width:100%;p{font-size:17px;width:80%;&:first-child{font-weight:500;}}a{color:inherit;text-decoration:underline;word-break:keep-all;}"]),o=n(85893),i=function(e){var t=e.type,n=e.state;return(0,o.jsx)(r,{children:"spam"===n?(0,o.jsxs)(o.Fragment,{children:[(0,o.jsxs)("p",{children:["This"," ",t," ","has been flagged as spam by our system."," ","Please do not attempt to re-post this"," ",t,"."]}),(0,o.jsxs)("p",{children:["If you believe this was a mistake,"," ","please contact"," ",(0,o.jsx)("a",{href:"mailto:community-spam@digitalocean.com",children:"community-spam@digitalocean.com"})," ","to appeal."]})]}):(0,o.jsxs)("p",{children:["This community submission is"," ",(0,o.jsx)("b",{children:"currently under review"})," ","and must be approved by a site moderator before being publicly available."]})})}},81042:function(e,t,n){"use strict";n.d(t,{jR:function(){return a},qQ:function(){return i}});var r=n(67294),o=n(85893),i=function(e){var t=(0,r.useRef)(null);return[function(){return window.scrollTo({top:t.current.offsetTop-(null!==e&&void 0!==e?e:100)})},t]},a=function(e,t){return(0,o.jsx)("div",{ref:t,children:e})};t.ZP=function(){var e=(0,r.useRef)(null);return[function(){return e.current.scrollIntoView()},e]}},89136:function(e,t,n){"use strict";n.d(t,{DC:function(){return i},L2:function(){return r},Pp:function(){return o}});var r=function(e){return window.localStorage.getItem(e)?JSON.parse(window.localStorage.getItem(e)):null},o=function(e,t){window.localStorage.setItem(e,JSON.stringify(t))},i=function(e){window.localStorage.getItem(e)&&window.localStorage.removeItem(e)}},21474:function(e,t){"use strict";t.Z=function(e){return e.id?e.first_name&&e.last_name?"".concat(e.first_name," ").concat(e.last_name):e.first_name||e.last_name||e.username:""}},23939:function(e,t,n){"use strict";var r=n(67294),o=n(45697),i=n.n(o);function a(){return a=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e},a.apply(this,arguments)}function l(e,t){if(null==e)return{};var n,r,o=function(e,t){if(null==e)return{};var n,r,o={},i=Object.keys(e);for(r=0;r<i.length;r++)n=i[r],t.indexOf(n)>=0||(o[n]=e[n]);return o}(e,t);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);for(r=0;r<i.length;r++)n=i[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(o[n]=e[n])}return o}var s=(0,r.forwardRef)((function(e,t){var n=e.color,o=void 0===n?"currentColor":n,i=e.size,s=void 0===i?24:i,c=l(e,["color","size"]);return r.createElement("svg",a({ref:t,xmlns:"http://www.w3.org/2000/svg",width:s,height:s,viewBox:"0 0 24 24",fill:"none",stroke:o,strokeWidth:"2",strokeLinecap:"round",strokeLinejoin:"round"},c),r.createElement("path",{d:"M22 11.08V12a10 10 0 1 1-5.93-9.14"}),r.createElement("polyline",{points:"22 4 12 14.01 9 11.01"}))}));s.propTypes={color:i().string,size:i().oneOfType([i().string,i().number])},s.displayName="CheckCircle",t.Z=s},59046:function(e,t,n){"use strict";var r=n(67294),o=n(45697),i=n.n(o);function a(){return a=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e},a.apply(this,arguments)}function l(e,t){if(null==e)return{};var n,r,o=function(e,t){if(null==e)return{};var n,r,o={},i=Object.keys(e);for(r=0;r<i.length;r++)n=i[r],t.indexOf(n)>=0||(o[n]=e[n]);return o}(e,t);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);for(r=0;r<i.length;r++)n=i[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(o[n]=e[n])}return o}var s=(0,r.forwardRef)((function(e,t){var n=e.color,o=void 0===n?"currentColor":n,i=e.size,s=void 0===i?24:i,c=l(e,["color","size"]);return r.createElement("svg",a({ref:t,xmlns:"http://www.w3.org/2000/svg",width:s,height:s,viewBox:"0 0 24 24",fill:"none",stroke:o,strokeWidth:"2",strokeLinecap:"round",strokeLinejoin:"round"},c),r.createElement("path",{d:"M18 13v6a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2V8a2 2 0 0 1 2-2h6"}),r.createElement("polyline",{points:"15 3 21 3 21 9"}),r.createElement("line",{x1:"10",y1:"14",x2:"21",y2:"3"}))}));s.propTypes={color:i().string,size:i().oneOfType([i().string,i().number])},s.displayName="ExternalLink",t.Z=s},16496:function(e){!function(){var t=["direction","boxSizing","width","height","overflowX","overflowY","borderTopWidth","borderRightWidth","borderBottomWidth","borderLeftWidth","borderStyle","paddingTop","paddingRight","paddingBottom","paddingLeft","fontStyle","fontVariant","fontWeight","fontStretch","fontSize","fontSizeAdjust","lineHeight","fontFamily","textAlign","textTransform","textIndent","textDecoration","letterSpacing","wordSpacing","tabSize","MozTabSize"],n="undefined"!==typeof window,r=n&&null!=window.mozInnerScreenX;function o(e,o,i){if(!n)throw new Error("textarea-caret-position#getCaretCoordinates should only be called in a browser");var a=i&&i.debug||!1;if(a){var l=document.querySelector("#input-textarea-caret-position-mirror-div");l&&l.parentNode.removeChild(l)}var s=document.createElement("div");s.id="input-textarea-caret-position-mirror-div",document.body.appendChild(s);var c=s.style,d=window.getComputedStyle?window.getComputedStyle(e):e.currentStyle,u="INPUT"===e.nodeName;c.whiteSpace="pre-wrap",u||(c.wordWrap="break-word"),c.position="absolute",a||(c.visibility="hidden"),t.forEach((function(e){u&&"lineHeight"===e?c.lineHeight=d.height:c[e]=d[e]})),r?e.scrollHeight>parseInt(d.height)&&(c.overflowY="scroll"):c.overflow="hidden",s.textContent=e.value.substring(0,o),u&&(s.textContent=s.textContent.replace(/\s/g,"\xa0"));var p=document.createElement("span");p.textContent=e.value.substring(o)||".",s.appendChild(p);var m={top:p.offsetTop+parseInt(d.borderTopWidth),left:p.offsetLeft+parseInt(d.borderLeftWidth),height:parseInt(d.lineHeight)};return a?p.style.backgroundColor="#aaa":document.body.removeChild(s),m}"undefined"!=typeof e.exports?e.exports=o:n&&(window.getCaretCoordinates=o)}()}}]);